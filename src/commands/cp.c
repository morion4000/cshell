/*******************************************************************************
**
** Module Name: cp.c
**
** Project Name: UNIX CSHell
**
********************************************************************************
**
** Created By: moraru.ionut
**
** Description: Implementation of the UNIX cp command;
**
********************************************************************************/

int com_cp (int argc, char **argv) {
	// Definition of local variables;
	int o;
	char *source = NULL, *dest = NULL;
	int i_flag = 0, r_flag = 0, v_flag = 0;

	/*
	 * Define text help and
	 * version commands;
	 */
	char * const help = "Usage: cp [OPTION] SOURCE DEST\n Copy SOURCE to DEST.\n\nParameters:\n\t-h, shows this help\n\t-u, shows version and author\n\t-i, prompt before overwrite\n\t-r, -R, copy directories recursively\n\t-v, explain what is being done\n";
	char * const author = " Author: Moraru Ionut\n Version: 1.0.3\n";

	// Reseting getopt internal index;
	optind = 0;

	while ((o = getopt(argc, argv, "huirRv")) != -1) {
	switch(o) {
		case 'h':
			fprintf(stdout, "%s\n",help);
			return 0;
		break;
		case 'u':
			fprintf(stdout, "%s\n",author);
			return 0;
		break;
		case 'i':
			i_flag = 1;
		 break;
		case 'r':
		case 'R':
			r_flag = 1;
		break;
		case 'v':
			v_flag = 1;
		break;
		case '?':
		default:
			abort();
		}
	}

	if(argc < 3) {
		fprintf(stderr, "Please enter SOURCE and DESTINATION.\n");
		return -1;
	}

	source = argv[argc-2];
	dest = argv[argc-1];

	if(is_dir(source) && !is_dir(dest)) {
		fprintf(stderr, "Cannot copy directory to file.\n");
		return -1;
	}

	/* file to file case */
	if((!is_dir(source) && !is_dir(dest)) || (!is_dir(source) && is_dir(dest))) {

		/* file to dir case */
		if(!is_dir(source) && is_dir(dest)) {
			if(dest[strlen(dest)-1] != '/')
				strcat(dest, "/");
			strcat(dest, source);
		}

		if(i_flag) {
			char ch;

	 		printf("DESTINATION file already exists. Overwrite? (y/n): ");
			ch = getchar();
			if(toupper(ch) != 'Y') {
				return 1;
			}
		}

		if(copy_file(source, dest)) {
			if(v_flag)
				fprintf(stdout, "%s copied to %s\n", source, dest);

			return 0;
		}

		return -1;
	} else
	if(is_dir(source) && is_dir(dest)) {
		/* dir to dir case */
		/*
		 * TODO: recursivity;
		 */
		if(r_flag) printf("-r parameter has not yet been implemented.\n");

		if(dest[strlen(dest)-1] != '/')
			strcat(dest, "/");
		strcat(dest, source);

		if(i_flag && is_dir(dest)) {
			char ch;

	 		printf("DESTINATION file already exists. Overwrite? (y/n): ");
			ch = getchar();
			if(toupper(ch) != 'Y') {
				return 1;
			}
		}

		if(make_dir(dest, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) {
			if(v_flag)
				printf("%s copied to %s\n", source, dest);
			return 0;
		}

		return -1;
	} else fprintf(stderr, "the universe is gonna implode\n");

	return 0;
}

