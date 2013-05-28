/*******************************************************************************
**
** Module Name: chmod.c
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

int com_chmod(int argc, char ** argv) {
	// Definition of local variables;
	int o = 0;
	int status = 1; // 1 for unsuccesfull;
	char * filename = NULL;
	int octal_mode = 0;

	int v_flag = 0, r_flag = 0;

	/*
	 * Define text help and
	 * version commands;
	 */
	char * const help = "Usage: chmod [OPTION] MODE FILE\n Change the mode of each FILE to MODE.\n\nParameters:\n\t-h, shows this help\n\t-u, shows version and author\n\t-v,  output a diagnostic for every file processed\n\t-r, -R, change files and directories recursively (to be implemented)\n\nDISCLAIMER:\n * Only octal mode supported,\n * DO NOT enter modes starting with 0. ex: 0777 -> 777\n";
	char * const author = " Author: Moraru Ionut\n Version: 1.0.2\n";

	// Reseting getopt internal index;
	optind = 0;

	while ((o = getopt(argc, argv, "huvrR")) != -1) {
	switch(o) {
		case 'h':
			fprintf(stdout, "%s\n", help);
			return 0;
		break;
		case 'u':
			fprintf(stdout, "%s\n", author);
			return 0;
		break;
		case 'v':
			v_flag = 1;
		break;
		case 'r':
		case 'R':
			r_flag = 1;
		break;
		case '?':
			return 1;
		default:
			abort();
		}
	}
	/*
	 * TODO: Implement "[ugoa]*([-+=]([rwxXst]*|[ugo])+" mode and recursivity;
	 */
	// Check for the number of parameters;
	if(argc > 2) {
		filename = argv[argc-1];
		octal_mode = (int)argv[argc-2];

		/*
		 * TODO: Check to see if file exists but first check permissions
		 * that might prevent from checking;
		if(!exists(filename)) {
			fprintf(stderr, "The path does not exist.\n");
			return 1;
		}
		*/
	} else {
		fprintf(stderr, "Too few parameters. Type 'chmod -h' for a detailed list of parameters.\n");
		return 1;
	}

	status = chmod(filename, (mode_t) octal_mode);

	if(status == 0 && v_flag) {
		fprintf(stdout, "Changed mode of file %s.\n", filename);
	}

	return status;
}
