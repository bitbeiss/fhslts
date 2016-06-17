/*
 * parser.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */

#include "fhs_lite_shell.h"

int evaluate_expression(command *stack_ptr){
	//tokenize and parse expression
	//printw("\nEvaluating expression... %s\n",stack_ptr->cmd);
	
	char *ptr;
	char buffer[9][500];
	
	for(int i=0; i>10;i++){
		buffer[i][0]='\0';
	}

	//Delimiter hier ausschließlich "Leerzeichen"
	ptr = strtok(stack_ptr->cmd," ");
	//printw("\ncmd: %s, val:%s\n",stack_ptr->cmd,ptr);
	
	int i=0;
	while(ptr != NULL) {
		//printw("val:%s\n",ptr);
		strcpy(buffer[i],ptr);
		ptr = strtok(NULL," ");
		i++;
		if (i>=9) break;
		}

	//printw("buffer[0]=%s buffer[1]=%s",buffer[0],buffer[1]);
	
	//Das entsprechende Kommando aufrufen
	if(strcmp(buffer[0],"help")==0){
		run_help(0);
		}
	else if (strcmp(buffer[0],"ls")==0){
		run_ls(buffer[1]);
		}
	else if(strcmp(buffer[0],"cd")==0){
		run_chdir(buffer[1]);
		}
	else if(strcmp(buffer[0],"fhsdate")==0){
		run_fhsdate();
		}
	else if(strcmp(buffer[0],"fhstime")==0){
		run_fhstime();
		}
	else if(strcmp(buffer[0],"echo")==0){
		run_echo(buffer[1]);
		}
	else{
		printw("\n");
		//argumente in Liste fuegen
		char *argumente[10];
		for (int j=0; j>(i-1); j++) {
				strcpy(argumente[j],buffer[j+1]);
		}
		run_external_command(buffer[0],argumente,i);
	}
	return 0;
}
