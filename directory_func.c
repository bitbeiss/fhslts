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
		run_help(2);
		return -1;
	}
	else {
		chdir(parameter);
	}
	return 0;
	}

int run_getcwd(){
	char *cwd=NULL;
    	getcwd(cwd,sizeof(cwd));
    	if (cwd==NULL) {
		set_term(stderr_term);
		fprintf(stderr, "\nFehler bei getcwd Aufruf: %s\n", strerror(errno));
		set_term(console_term);
    	} 
    	else {
		printw("%s\n",cwd);
		return 0;
    	}
    return -1;
}

int run_ls(char *parameter){
	struct stat myFile;
	if (strcmp(parameter,"\0")==0) {		//Wenn der Parameter leer ist
		
				run_help(1); 			//Hilfe aufrufen
				return -1;
			}
	else if (stat(parameter, &myFile) < 0) {
		set_term(stderr_term);
		fprintf(stderr,"Error: file or path not valid!\n");
		refresh();
		set_term(console_term);
		run_help(1);
		return -1;
	}
	
	else if (!S_ISDIR(myFile.st_mode)) {
    	// Exists but is not a directory
    	exit(1);
	}
	
	else {
		DIR *dp;
		struct dirent *ep;

		dp = opendir ("./");
		printw("\n");
		if (dp != NULL)
			{
				while ((ep = readdir (dp)) )
				printw("%s\n",ep->d_name);
				(void) closedir (dp);
			}
	
		else {
			perror ("Couldn't open the directory");
		}
  
	}
	return 0;
}
