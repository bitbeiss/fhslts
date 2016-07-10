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
int run_external_command(char *kommando, char *argumente[], int nargs){
	//keine Argumente...
	if (nargs==0) {
		strcpy(argumente[0],kommando);
		argumente[1] = NULL;
	}


	pid_t process_id;
	int exec_ok;
	int status;

	// Prozess clonen, um zu vermeiden, dass der Originalprozess/die Shell im Fehlerfall terminiert wird
	process_id = fork();
	//Kindprozess: Ausfuehren ohne Reue... :D
	if (process_id == 0) {
		// Kindprozess laedt das Kommando in den laufenden Prozess
		// erste Uebergabe ist das Kommando, 2. Uebergabe sind die Argumente
		exec_ok = execvp(kommando , argumente);
		if(exec_ok == -1) {

			printw("\nError: %s\n",strerror(errno));
			endwin();
			exit(1);
		}
		return 0;
	}
	//Kindprozess kann nicht starten - Fehler
	else if (process_id <0) {
		printw("\nError: %s\n",strerror(errno));
		return 1;
	}
	//Auf den Kindprozess warten
	else {
		do {
			waitpid(process_id, &status, WUNTRACED);
		}
		while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 0;
}
