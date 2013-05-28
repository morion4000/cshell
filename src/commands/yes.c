/*******************************************************************************
**
** Module Name: yes.c
**
** Project Name: UNIX CSHell
**
********************************************************************************
**
** Created By: moraru.ionut
**
** Description: Implementation of the UNIX yes command;
**
********************************************************************************/

int com_yes(int argc, char ** argv) {
	/*
	 * Registering the handler, catching
	 * SIGINT signals
	 */
	signal(SIGINT, signal_handler);

	// Definition of local variables;
	int o;

	/*
	 * Define text help and
	 * version commands;
	 */
	char * const help = "Usage: yes\n Repeatedly output a line with all specified STRING, or 'y'.\n\nParameters:\n\t-h, shows this help\n\t-u, shows version and author\n";
	char * const author = " Author: Moraru Ionut\n Version: 1.0.1\n";

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

	if(argc < 2)
		argv[1] = "y";
	while(1) {
		printf("%s\n", argv[1]);
	}
}
