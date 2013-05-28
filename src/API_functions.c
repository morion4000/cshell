/*******************************************************************************
**
** Module Name: API_functions.c
**
** Project Name: UNIX CSHell
**
********************************************************************************
**
** Created By: moraru.ionut
**
** Description: Functions used across the project;
**
********************************************************************************/

/*
 * Functions definition;
 */

int is_dir(const char*);
int exists(char *);
char *get_pwd();
int copy_file(char *, char *);
int make_dir(char *, mode_t);
int rm_dir(char *, int, int);
int confirm(char *, char *);
int substr_count(char, char const *);
char **break_string_into_array(char *, char *);

/*
 * Checks to see if the path is a directory;
 */

int is_dir(const char *dname) {
	struct stat sbuf;

	if (lstat(dname, &sbuf) == -1) {
		return 0;
	}

	if(S_ISDIR(sbuf.st_mode)) {
		return 1;
	}

	return 0;
}

/*
 * Checks to see if the path exists on disk;
 */

int exists(char * file) {
	if(fopen(file, "rb") != NULL) {
		return 1;
	}

	return 0;
}

/*
 * Gets current working directory;
 */

char * get_pwd() {
	long size;
	char *buf;
	char *ptr;

	size = pathconf(".", _PC_PATH_MAX);

	if ((buf = (char *)malloc((size_t)size)) != NULL) {
		ptr = getcwd(buf, (size_t)size);
		return ptr;
	}

	return NULL;
}

/*
 * Copies one file to another;
 */

int copy_file(char * source, char * destination) {
	char ch;
	FILE *in, *out;

	// open SOURCE file;
	if((in=fopen(source, "rb")) == NULL) {
		fprintf(stderr, "The SOURCE file does not exists.\n");
	return -1;
	}

	// open DESTINATION file;
	if((out=fopen(destination, "wb")) == NULL) {
		fprintf(stderr, "Cannot open DESTINATION for writting.\n");
	return -1;
	}

	// copy character by character from SOURCE to DESTINATION;
	while(!feof(in)) {
		ch = getc(in);
		if(ferror(in)) {
			printf("Read Error.\n");
			clearerr(in);
		break;
		} else {
			if(!feof(in)) putc(ch, out);
				if(ferror(out)) {
					printf("Write Error.\n");
					clearerr(out);
			break;
			}
		}
	}

	// cleanup;
	fclose(in);
	fclose(out);

	return 1;
}

/*
 * Makes a directory;
 */

int make_dir(char * path, mode_t cmask) {
	return mkdir(path, cmask);
}

/*
 * Recursively removes a directory;
 */

int rm_dir(char * path, int i_flag, int v_flag) {
	DIR *pdir = NULL;
	struct dirent *pent = NULL;
	char * file;
	int counter = 1;

	if (path[strlen(path)-1] != '/')
		strcat(path, "/");

	pdir = opendir (path);

	if (pdir == NULL) {
		return 0;
	}

	while ((pent = readdir (pdir))) {
		if (counter > 2) {
			int i;

			for (i = 0; i < 256; i++) file[i] = '\0';

		 	strcat(file, path);

		 	if (pent == NULL) {
		      		return 0;
		 	}

			strcat(file, pent->d_name);

			if (is_dir(file)) {
				// if confirmed recursivelly delete directory;
				if(i_flag && confirm("Are you sure you want to delete %s? (y/n): ", file)) {
					rm_dir(file, i_flag, v_flag);
				}
			} else {
				// if confirmed delete file;
				if(i_flag && confirm("Are you sure you want to delete %s? (y/n): ", file) && remove(file)) {
					// verbose;
					if(v_flag)
						fprintf(stdout, "%s has been deleted.\n", file);
				}
			}
		} counter++;
	}

	closedir (pdir);

	rmdir(path);

	// verbose;
	if(v_flag)

		fprintf(stdout, "%s has been deleted.\n", path);

	return 1;
}

/*
 * Prompts a confirmation message;
 */

int confirm(char * message, char * path) {
	char ch;

	// print custom message;
	fprintf(stdout, message, path);
	ch = getchar();

	// if not Y(es) return false else return true;
	if(toupper(ch) != 'Y') {
		return 0;
	}

	return 1;
}

/*
 * Search the number of occurences of a
 * character in a string;
 */

int substr_count(char needle, char const *haystack) {
    int k = 0;
    while(*haystack++) {
        if(needle == *haystack)
            k++;
    }

    return k;
}

/*
 * Break string into array;
 */

char **break_string_into_array(char *string, char *delimiter) {
    char **array = NULL;
    char *result = NULL;
    int arraycount = 0;

    array = malloc(MAX_COMS * sizeof(char *));

    result = strtok(string, delimiter);

    while (result != NULL) {
        array[arraycount] = malloc(sizeof(result));
        strcpy(array[arraycount], result);
        result = strtok(NULL, delimiter);
        arraycount++;
    }

    free(result);

    return array;
}
