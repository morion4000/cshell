/*******************************************************************************
**
** Module Name: cd.c
**
** Project Name: UNIX CSHell
**
********************************************************************************
**
** Created By: moraru.ionut
**
** Description: Implementation of the UNIX cd command;
**
********************************************************************************/

int com_cd(int argc, char ** argv) {
	// Definition of local variables;
	char * directory; // Directory path;
	int o;

	/*
	 * Define text help and
	 * version commands;
	 */
	char * const help = "Usage: cd [PATH]\n Change directory.\n\nParameters:\n\t-h, shows this help\n\t-u, shows version and author\n";
	char * const author = " Author: Moraru Ionut\n Version: 1.1.1\n";

	// Reseting getopt internal index;
	optind = 0;

	while ((o = getopt(argc, argv, "hu")) != -1) {
	switch(o) {
		case 'h':
			fprintf(stdout, "%s\n",help);
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

	if(strcmp(argv[argc-1], "cd") == 0) {
		// If no parameters change to home directory;
		directory = getenv("HOME");
	} else {
		// else change to specified directory;
		directory = argv[argc-1];
		// check to see if directory exits;
		if(!is_dir(directory)) {
			fprintf(stderr, "The specified path does not exits.\n");
			return 0;
		}
	}

	return chdir (directory);
}

