/*******************************************************************************
**
** Module Name: ls.c
**
** Project Name: UNIX CSHell
**
********************************************************************************
**
** Created By: moraru.ionut
**
** Description: Implementation of the UNIX ls command;
**
********************************************************************************/

int com_ls(int argc, char **argv) {
	// Definition of local variables;
	DIR *dir;
	struct dirent *dp;
	struct stat     statbuf;
	struct passwd  *pwd;
	struct group   *grp;
	struct tm      *tm;
	char            datestring[256];

	char * dir_path = ".";

	int l_flag = 0, s_flag = 0, a_flag = 0, F_flag = 0;
	int o;

	/*
	 * Define text help and
	 * version commands;
	 */
	char * const help = "Usage: ls [OPTION] [FILE]\n List information about the FILE.\n\nParameters:\n\t-h, shows this help\n\t-u, shows version and author\n\t-l, use a long listing format\n\t-s, print the size of each file, in blocks\n\t-a, do not ignore entries starting with .\n\t-F, append indicator (one of */=>@|) to entries\n";
	char * const author = " Author: Moraru Ionut\n Version: 1.0.1\n";

	// Reseting getopt internal index;
	optind = 0;

	while ((o = getopt(argc, argv, "hulsaF")) != -1) {
	 switch(o) {
		case 'h':
			fprintf(stdout, "%s\n", help);
			return 0;
		break;
		case 'u':
			fprintf(stdout, "%s\n", author);
			return 0;
		break;
		case 'l':
			l_flag = 1;
		break;
		case 's':
			s_flag = 1;
		break;
		case 'a':
			a_flag = 1;
		break;
		case 'F':
		 	F_flag = 1;
		break;
		case '?':
		default:
			abort();
		}
	}

	dir_path = argv[argc-1];

        if(a_flag || s_flag || l_flag || F_flag) {
		if(!is_dir(dir_path)) {
			dir_path = ".";
		}
	} else {
		if(strcmp(argv[argc-1], "ls") == 0)
			dir_path = ".";
	}

	if ((dir = opendir (dir_path)) == NULL) {
        	fprintf (stderr, "%s is not a directory.\n", dir_path);
        	return -1;
	}

	while ((dp = readdir (dir)) != NULL) {
		if(!a_flag) {
			char c = dp->d_name[0];
			if(c == '.') continue;
		}

		if(stat(dp->d_name, &statbuf) == -1)
			;//continue;

		if(l_flag) {
			if(!a_flag && (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)) {
                	        continue;
			}

			/* Print out type, permissions, and number of links. */
			printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
			printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
			printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
			printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
			printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
			printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
			printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");

			printf("%4d", statbuf.st_nlink);

		    	/* Print out owner's name if it is found using getpwuid(). */
		   	if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
		    		printf(" %-8.8s", pwd->pw_name);
			//else
			//printf(" %-8d", statbuf.st_uid);

	   		/* Print out group name if it is found using getgrgid(). */
		   	if ((grp = getgrgid(statbuf.st_gid)) != NULL)
			        printf(" %-8.8s", grp->gr_name);
			//else
			//printf(" %-8d", statbuf.st_gid);

			/* Print size of file. */
			printf(" %9jd", (intmax_t)statbuf.st_size);

			tm = localtime(&statbuf.st_mtime);

	   		/* Get localized date string. */
			strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
			printf(" %s %s\n", datestring, dp->d_name);

		} else if(s_flag) {
			if(!a_flag && (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)) {
                	        continue;
			}

			printf("%ld", statbuf.st_blocks/2);
			printf(" %s\t", dp->d_name);
		} else if(F_flag) {
			if(!a_flag && (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)) {
                	        continue;
			}

			printf("%s", dp->d_name);
			if(S_ISDIR(statbuf.st_mode))  {
				printf("/\t");
			} else if(S_ISLNK(statbuf.st_mode)) {
				printf("@\t");
			} else if(statbuf.st_mode & S_IXUSR) {
                        	printf("*\t");
                        } else {
				printf("\t");
			}
		} else {
			if(!a_flag && (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)) {
                	        continue;
			}

			printf("%s\t", dp->d_name);
		}

	}

	printf("\n");

	closedir(dir);

	return 0;
}
