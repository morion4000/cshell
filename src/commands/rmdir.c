/*******************************************************************************
**
** Module Name: rmdir.c
**
** Project Name: UNIX CSHell
**
********************************************************************************
**
** Created By: moraru.ionut
**
** Description: Implementation of the UNIX rmdir command;
**
********************************************************************************/

int com_rmdir(int argc, char ** argv) {
	// Definition of local variables;
	char * path = argv[argc-1];

	int o;
	int p_flag = 0, v_flag = 0;

	/*
	 * Define text help and
	 * version commands;
	 */
	char * const help = "Usage: rmdir [OPTION] DIRECTORY\n Remove the DIRECTORY, if it is empty.\n\nParameters:\n\t-h, shows this help\n\t-u, shows version and author\n\t-p, Remove DIRECTORY and its ancestors\n\t-v, output a diagnostic for every directory processed\n";
	char * const author = " Author: Moraru Ionut\n Version: 1.0.2\n";

	// Reseting getopt internal index;
	optind = 0;

	while ((o = getopt(argc, argv, "hupv")) != -1) {
	switch(o) {
		case 'h':
			fprintf(stdout, "%s\n", help);
			return 0;
		break;
		case 'u':
			fprintf(stdout, "%s\n", author);
			return 0;
		break;
	 	case 'p':
			p_flag = 1;
		break;
		case 'v':
			v_flag = 1;
		break;
		case '?':
		default:
			abort();
	 	}
	}

	if(is_dir(path)) {
		if(p_flag) {
			/*
			 * TODO: parameter not yet suported;
		         */
			fprintf(stdout, "Parameter not yet supported.\n");
		} else {
			if(rmdir(path)) {
				if(v_flag)
					fprintf(stdout, "Directory deleted.\n");
			} else {
				fprintf(stderr, "Directory not empty.\n");
			}
		}
	} else fprintf(stderr, "Directory does not exit on disk.\n");

	return 0;
}
