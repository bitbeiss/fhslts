/*
 * parser.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * 			Tokenize and parse input on shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */

#include "fhs_lite_shell.h"

int evaluate_expression(command *stack_ptr, DIR_SAVE *verz_buff){
	//tokenize and parse expression
	//printw("\nEvaluating expression... %s\n",stack_ptr->cmd);

	char *ptr;
	char buffer[9][MAX_CHARS_PER_LINE];
	


	for(int i=0; i<MAX_ECHO_BUFFER_ARGS;i++){
		buffer[i][0]='\0';
	}


	int number_of_param=0;
	//Delimiter hier ausschließlich "Leerzeichen"
	

	ptr = strtok(stack_ptr->cmd," ");
	//printw("\ncmd: %s, val:%s\n",stack_ptr->cmd,ptr);


	while(ptr != NULL) {
		//printw("val:%s\n",ptr);
		strcpy(buffer[number_of_param],ptr);
		ptr = strtok(NULL," ");
		number_of_param++;
		if (number_of_param>=MAX_PARAMETERS) break;
		}



	//printw("buffer[0]=%s buffer[1]=%s",buffer[0],buffer[1]);
	
	//Das entsprechende Kommando aufrufen
	if (strcmp(buffer[0],"help")==0) {
		//printw("Running help\n");
			//Zu welchem Thema (falls Parameter vorhanden)
			//die Hilfefunktion aufgerufen werden soll...
			if(strcmp(buffer[1],"ls")==0) {
				run_help(LS_ERROR); }
			else if(strcmp(buffer[1],"cd")==0) {
				run_help(CD_ERROR); }
			else if(strcmp(buffer[1],"fhsdate")==0) {
				run_help(FHSDATE_ERROR); }
			else if(strcmp(buffer[1],"fhstime")==0) {
				run_help(FHSTIME_ERROR); }
			else if(strcmp(buffer[1],"history")==0) {
				run_help(HISTORY_ERROR); }
			else if(strcmp(buffer[1],"echo")==0) {
				run_help(ECHO_ERROR); }
			else if(strcmp(buffer[1],"pwd")==0) {
				run_help(PWD_ERROR); }
			else if(strcmp(buffer[1],"execute")==0) {
				run_help(EXECUTE_ERROR); }
			else if(strcmp(buffer[1],"pushd")==0) {
				run_help(PUSHD_ERROR); }
			else if(strcmp(buffer[1],"popd")==0) {
				run_help(POPD_ERROR); }
			else {
				run_help(0); }
		}
	else if (strcmp(buffer[0],"ls")==0) {
		run_ls(buffer[1]);
		}
	else if(strcmp(buffer[0],"cd")==0) {
		printw("\n");
		run_chdir(buffer[1]);
		}
	else if(strcmp(buffer[0],"pwd")==0) {
			//cwd[0]='\0';
			printw("\n");
			run_getcwd();
			printw("\n");
			}
	else if(strcmp(buffer[0],"fhsdate")==0) {
		run_fhsdate();
		}
	else if(strcmp(buffer[0],"fhstime")==0) {
		run_fhstime();
		}
	else if(strcmp(buffer[0],"echo")==0) {
		run_echo(buffer,MAX_ECHO_BUFFER_ARGS);
		}
	else if(strcmp(buffer[0],"history")==0) {
		show_stack(stack_ptr);
	}
	else if(strcmp(buffer[0],"pushd")==0) {
		run_pushd(verz_buff);
	}
	else if(strcmp(buffer[0],"popd")==0) {
		run_popd(verz_buff);
	}
	else if(strcmp(buffer[0],"exec")==0) {
		printw("\n");
		//Argumente in Liste fuegen
		char *argumente[MAX_CHARS_PER_LINE];
		int j;
		//das erste argument muss nach Konvention gleich dem Dateinamen des auszufuehrenden Programmes sein.
		argumente[0]=buffer[0];
		for (j=1; j<(number_of_param-1); j++) {
			strcpy(argumente[j+1],buffer[j+1]);
		}
		//zu uebergebendes Array sollte NULL terminiert sein.
		argumente[j+1] = NULL;
		run_external_command(buffer[1],argumente,number_of_param);
	}
	else if(strcmp(buffer[0],"quit")==0) {
		printw("\n");
		endwin();
		exit(0);
	}
	else {
		//Argumente in Liste fuegen
		char *argumente[MAX_CHARS_PER_LINE];
		int j;
		argumente[0]=buffer[0];
		for (j=0; j<(number_of_param-1); j++) {
				strcpy(argumente[j+1],buffer[j+1]);
		}
		//zu uebergebendes Array sollte NULL terminiert sein.
		argumente[j+1] = NULL;
		run_external_command(buffer[0],argumente,number_of_param);
	}
return 0;
}
