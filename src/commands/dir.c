/*******************************************************************************
**
** Module Name: dir.c
**
** Project Name: UNIX CSHell
**
********************************************************************************
**
** Created By: moraru.ionut
**
** Description: Implementation of the UNIX dir command;
**
********************************************************************************/

int com_dir(int argc, char **argv) {
	// Definition of local variables;
	DIR *dir;
	struct dirent *dp;
	int o;

	char * dir_path = ".";

	/*
	 * Define text help and
	 * version commands;
	 */
	char * const help = "Usage: dir [FILE]\n List information about the FILE.\n\nParameters:\n\t-h, shows this help\n\t-u, shows version and author\n";
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

	if ((dir = opendir (dir_path)) == NULL) {
        	fprintf (stderr, "%s is not a directory.\n", dir_path);
        	return 1;
	}

	while ((dp = readdir (dir)) != NULL) {
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
			continue;
		}
		char c = dp->d_name[0];
		if(c == '.') continue;

		fprintf(stdout, "%s\t", dp->d_name);
	}

	fprintf(stdout, "\n");

	closedir(dir);

	return 0;
}
