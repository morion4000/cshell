/*******************************************************************************
**
** Module Name: pwd.c
**
** Project Name: UNIX CSHell
**
********************************************************************************
**
** Created By: moraru.ionut
**
** Description: Implementation of the UNIX pwd command;
**
********************************************************************************/

int com_pwd(int argc, char **argv) {
	// Definition of local variables;
	char * pwd = NULL;
	int o;

	/*
	 * Define text help and
	 * version commands;
	 */
	char * const help = "Usage: pwd\n Print working directory.\n\nParameters:\n\t-h, shows this help\n\t-u, shows version and author\n";
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

	if((pwd = get_pwd())) {
		printf("%s\n", get_pwd());
		return 0;
	}

	return -1;
}
