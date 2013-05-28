/*******************************************************************************
**
** Module Name: exec.c
**
** Project Name: UNIX CSHell
**
********************************************************************************
**
** Created By: moraru.ionut
**
** Description: Execute external commands;
**
********************************************************************************/

int com_exec(int argc, char **argv) {
	/*
	 * TODO: fork and execl;
         */
	if(argc > 1)
		system(argv[1]);
	else
		fprintf(stderr, "Please enter an external command to execute!\n");

	return 0;
}
