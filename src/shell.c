#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>
#include <signal.h>
#include <fcntl.h>

#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

#define MAX_ARGS 20
#define MAX_COMS 20
#define ARGS_DELIMITER " "

// Functions declaration
int com_help(),
	com_dummy(),
	com_printenv(int, char**),
	com_pwd(int, char**),
	com_cp(int, char**),
	com_ls(int, char**),
	com_dir(int, char**),
	com_cd(int, char**),
	com_mkdir(int, char**),
	com_rm(int, char**),
	com_rmdir(int, char**),
	com_chmod(int, char**),
	com_yes(int, char**),
	com_exec(int, char**);

void com_exit();

// Catch signal;
void signal_handler(int);

int com_exe(char *);

/*
 * Include API functions;
 */
#include "API_functions.c"
/*
 * Header file to include all commands;
 */
#include "include_commands.h"

// Global variables used in program
int argcount;
char **argvector;
int last_executed_command_code;

// struct COMMAND definition
typedef struct {
        char *name; /* command line name */
        Function *func; /* internal function triggered by the command */
        char *doc; /* short description */
} COMMAND;

// struct COMMAND content
COMMAND cmd[] = {
                {"?", com_help, "Display the help."},
                {"dummy", com_dummy, "Dummy function."},
                {"printenv", com_printenv, "Print enviroment variables."},
                {"exit", com_exit, "Exit the shell."},
                {"pwd", com_pwd, "Print working directory."},
                {"ls", com_ls, "List information about the FILE."},
                {"cp", com_cp, "Copies SOURCE to DESTINATION."},
                {"dir", com_dir, "List information about the FILE."},
                {"yes", com_yes, "Repeatedly output a line with all specified STRING, or 'y'."},
                {"cd", com_cd, "Change the current directory."},
                {"mkdir", com_mkdir, "Create a DIRECTORY, if it does not already exist."},
                {"rmdir", com_rmdir, "Remove the DIRECTORY, if it is empty."},
                {"rm", com_rm, "Remove (unlink) the FILE."},
                {"chmod", com_chmod, "Change the mode of each FILE to MODE."},
                {"exec", com_exec, "Execute external commands."},
                { (char *)NULL, (Function *)NULL, (char *)NULL }
                };

int main (int argc, char **argv) {
	/*
	 * Registering the handler, catching
	 * SIGINT signals
	 */
	signal(SIGINT, signal_handler);

    char *line = NULL;
    int done = 0;
    int j = 0;

        /* loop until user quits */
        for ( ; done == 0; )
        {
            line = readline (strcat(get_pwd(), "$ "));

            if (strlen(line) > 0) {
                    add_history(line);

			/*
 			 * Secvential commands;
 			 */

			// Allocate memory and set variables;
			char **sec_coms = NULL; // secvential commands vector;
            int sec_coms_no = 0;

			sec_coms = malloc(MAX_COMS * sizeof(char *));

			sec_coms_no = substr_count(';', line)+1; // Calculate the number of secvential commands;
			sec_coms = break_string_into_array(line, ";");

			for(j = 0; j < sec_coms_no; j++) {
			    /*
	 			 * Operational commands;
	 			 */

                // Allocate memory and set variables;
                char **op_coms = NULL; // operational commands vector;
                char *operational_command_type = NULL;

                op_coms = malloc(2 * sizeof(char *)); // Max 2 operational commands;

                // Set the command_type;
                if(strstr(sec_coms[j], "&&")) operational_command_type = "&&";
                if(strstr(sec_coms[j], "||")) operational_command_type = "||";

                if(operational_command_type) {
                    op_coms = break_string_into_array(sec_coms[j], operational_command_type);

                    // Execute first operational command;
                    /** Scraps from redirection tests;
                     * TODO: Redirection;
                    char *red_com = NULL;
                    red_com = malloc(sizeof(char *));
                    char red_type = NULL;

                    if((red_com = strstr(op_coms[0], ">")) != NULL) {
                        int fd;
                        red_type = *red_com++;
                        fd = open(*red_com, O_CREAT);
                        close(1);
                        dup(fd);
                        close(fd);
                    }
                    */

                    com_exe(op_coms[0]);

                    if(strcmp(operational_command_type, "&&") == 0) {
                        if(last_executed_command_code == 0) //successfull;
                            // Execute second operational command;
                            com_exe(op_coms[1]);
                    } else {
                        // operational_command_type == "||"
                        if(last_executed_command_code != 0) //unsuccessfull;
                            com_exe(op_coms[1]);
                    }
                } else {
                    // Execute secvential command;
                    com_exe(sec_coms[j]);
                }

                free(op_coms);

			}

			free(sec_coms);

        }

        free (line);
    }

    exit (0);
}

// Prints out the available internal command
int com_help(int argc, char **argv) {
        int i=0;

        printf("Shell's internal commands: \n\n");
        while ( cmd[i].name != NULL) {
                printf("%s - %s\n", cmd[i].name, cmd[i].doc);
                i++;
        }

        return 0;
}

// It searches for a command in cmd[] and returns a pointer to it. If no command found it returns NULL.
COMMAND* com_find (char* name) {
        int i;

        for (i = 0; cmd[i].name; i++)
                if (strcmp (name, cmd[i].name) == 0)
                        return (&cmd[i]);

        return ((COMMAND *)NULL);
}

// Dummy function that prints the number of arguments passed and a list of each argument.
int com_dummy(int argc, char **argv) {
	int i;

	printf("Number of arguments: %i\n", argc);
	for (i = 0; i < argc; i++)
	printf("arg[%i]= %s\n", i, argv[i]);

	return 0;
}

/*
 * function that executes you command from the command line.
 *
 * 'argvector' supports only 20 arguments in a row. For more adjust MAX_ARGS;
 *
 */
int com_exe(char *cmdline) {
        ///printf("\n%s\n", cmdline);

        COMMAND *command;

        // initialize the dynamically sized vector
        argvector = malloc(MAX_ARGS * sizeof(char *));

        // reset argcount to zero
        argcount = 0;

        char* result = NULL;

        result = strtok(cmdline, ARGS_DELIMITER);

        while ( result != NULL ) {
		argvector[argcount] = malloc(sizeof(result));
                strcpy(argvector[argcount], result);
                result = strtok(NULL, ARGS_DELIMITER);
                argcount++;
        }

        // use com_find to search for command name (first entry in argvector should be the command name)
        command = com_find(argvector[0]);
        if ( command == NULL )
                printf("Command not found. Use ? for help.\n");
        else { (void) signal(SIGINT, SIG_DFL);
                //printf("\n");
                last_executed_command_code = command->func(argcount, argvector);
                //printf("\n");
        }

    /*
	while (argcount > 0)
	   	free(argvector[--argcount]);
	free(argvector);
	*/


        return 0;
}

/* The signal handler function */
void signal_handler(int sig) {
	signal(SIGINT, signal_handler);
	printf("Signal handler. Type 'exit' to close session.\n");
	psignal(sig, "Signal");
}
