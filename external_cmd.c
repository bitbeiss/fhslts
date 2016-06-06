/*
 * external_cmd.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */
 
#include "fhs_lite_shell.h"

//Damit laesst sich ein externes commando ausführen - Uebergabe ist getokenizder String inkl. Kommando + Argumente
int run_external_command(char *command){


	pid_t process_id, waitprocess_id;
	int exec_ok;
	int status;
	process_id = fork();
	if (process_id == 0)
	{
		exec_ok = execvp(&(command[0]), &(command[1]));  //erste Übergabe ist das Kommando, 2. Übergabe sind die Argumente
		if(exec_ok == -1)
		{
			perror("Error: ");
		}
		return -1;
	}
	else if (process_id <0)
	{
		perror("Error: ");
		return -1;
	}
	else
	{
		do {
			waitprocess_id = waitpid(process_id, &status, WUNTRACED);
		}
		while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 0;
}
