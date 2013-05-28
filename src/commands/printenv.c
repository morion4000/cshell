/*******************************************************************************
**
** Module Name: printenv.c
**
** Project Name: UNIX CSHell
**
********************************************************************************
**
** Created By: moraru.ionut
**
** Description: Implementation of the UNIX printenv command;
**
********************************************************************************/

int com_printenv(int argc, char ** argv) {
	// Definition of local variables;
	int o, i = 0;

        extern char ** environ;

	/*
	 * Define text help and
	 * version commands;
	 */
	char * const help = "Usage: printenv\n Print enviroment variables.\n\nParameters:\n\t-h, shows this help\n\t-u, shows version and author\n";
	char * const author = " Author: Moraru Ionut\n Version: 1.0.2\n";

	// Reseting getopt internal index;
	optind = 0;

	while ((o = getopt(argc, argv, "hu")) != -1) {
	switch(o) {
		case 'h':
			fprintf(stdout, "%s\n", help);
			return 0;
		break;
		case 'u':
			fprintf(stdout, "%s\n", author);
			return 0;
		break;
		case '?':
			return 1;
		default:
			abort();
		}
	}

	while (environ[i])
		puts(environ[i++]);

	return 0;
}
