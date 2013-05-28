/*******************************************************************************
**
** Module Name: mkdir.c
**
** Project Name: UNIX CSHell
**
********************************************************************************
**
** Created By: moraru.ionut
**
** Description: Implementation of the UNIX mkdir command;
**
********************************************************************************/

int com_mkdir(int argc, char ** argv) {
	// Definition of local variables;
	int o;
	mode_t cmask;
	char * path;

	int m_flag = 0, p_flag = 0, v_flag = 0;

	/*
	 * Define text help and
	 * version commands;
	 */
	char * const help = "Usage: mkdir [OPTION] DIRECTORY\n Create the DIRECTORY, if it does not already exist.\n\nParameters:\n\t-h, shows this help\n\t-u, shows version and author\n\t-m, set file mode (as in chmod)\n\t-p, no error if existing, make parent directories as needed\n\t-v, print a message for each created directory\n";
	char * const author = " Author: Moraru Ionut\n Version: 1.1.2\n";

	// Reseting getopt internal index;
	optind = 0;

	while ((o = getopt(argc, argv, "humpv")) != -1) {
	switch(o) {
		case 'h':
			fprintf(stdout, "%s\n", help);
			return 0;
		break;
		case 'u':
			fprintf(stdout, "%s\n", author);
			return 0;
		break;
	 	case 'm':
			m_flag = 1;
	 	break;
	 	case 'p':
			p_flag = 1;
		break;
		case 'v':
			v_flag = 1;
		break;
		case '?':
			return 1;
		default:
			abort();
		}
	}

	if(argc < 2) {
		fprintf(stderr, "At least 1 parameter is required.\n");
	}

	path = argv[argc-1];

	cmask = (mode_t) 0777;

	if(make_dir(path, cmask)) {
		if(v_flag)
			printf("Created new directory: %s\n", path);
		return 0;
	}

	return 1;
}
