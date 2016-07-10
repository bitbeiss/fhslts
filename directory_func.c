/*
 * directory_func.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */
 
#include "fhs_lite_shell.h"

int run_chdir(char *parameter){
	if (strcmp(parameter,"..")==0){
		system("cd ..");
	}
	
	else if(strcmp(parameter,"")==0) { 
		run_help(CD_ERROR);
		return -1;
	}
	else {
		chdir(parameter);
	}
	return 0;
	}

int run_getcwd(){
	char cwd[MAX_LEN_CWD];
	cwd[0]='\0';
    getcwd(cwd,sizeof(cwd));
    if (strlen(cwd)==0) {
    	endwin();
    	fprintf(stderr, GET_CWD_MESSAGE);
    	exit(1);
    }
    else {
    	printw("%s",cwd);
		return 0;
    }
    PROMPT
    return -1;
}

int run_ls(char *parameter){
	struct stat myFile;

	//printw("\nparameter: %s\n",parameter);
	if(strlen(parameter)==0) {			// Wenn der Parameter leer ist
		strcpy(parameter,"./");			// Parameter auf das aktuelle Verzeichnis setzen

			}
	if (stat(parameter, &myFile) < 0) {
		printw(UNKNOWN_FILE_MESSAGE);
		refresh();
		run_help(LS_ERROR);
		return -1;
	}
	
	else if (!S_ISDIR(myFile.st_mode)) {
    	// Exists but is not a directory
		endwin();
		fprintf(stderr,FILE_EXISTS_BUT_NOT_DIR_MESSAGE);
    	exit(1);
	}
	
	else {
		DIR *dp;
		struct dirent *ep;

		dp = opendir (parameter);
		printw("\n");
		if (dp != NULL)
			{
				while ((ep = readdir (dp))!=NULL )
				printw("%s\n",ep->d_name);
				(void) closedir (dp);
			}
	
		else {
			printw(FILE_OPEN_MESSAGE);
			//perror(FILE_OPEN_MESSAGE);
		}
  
	}
	return 0;
}

