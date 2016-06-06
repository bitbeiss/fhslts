/*
 * pushd_popd.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */

#include "fhs_lite_shell.h"

//Speichert das aktuelle Verzeichnis in den Stack, Übergabe ist der ptr auf das zuletzt gespeicherte Verzeichnis
int run_pushd(DIR_SAVE *end_verz){
	char buffer[80];
	DIR_SAVE *ptr_help = end_verz;

	//Neues Verzeichnis-Element anlegen.
	if ((end_verz = malloc(sizeof(DIR_SAVE))) != NULL) {
		//Zeiger im neuen Element setzen.
		end_verz->previous = ptr_help;
		end_verz->next = NULL;
		
		//speichert aktuelles Verzeichnis
		if(NULL != getcwd(buffer,80)){
			strcpy(end_verz->directory,buffer);
		}
		else{
			printf("Konnte Verzeichnis nicht finden!");
			return -1;
		}

		//next Zeiger im darunterliegenden Element aktualisieren.
		end_verz->previous->next = end_verz;
		printf("Verzeichnis %s gespeichert", end_verz->directory);
		return 0;
	}
	else {
		printf("Allozierung des Speichers Verzeichnis fehlgeschlagen!\n");
		return -1;
		}
}

//wechselt in letztes gespeichertes Verzeichnis und löscht es aus dem Stack .. Übergabe ist der ptr auf das letzte Verzeichnis
int run_popd(DIR_SAVE *end_verz){
	char *help=NULL;
	DIR_SAVE *help_ptr;
	help_ptr = end_verz;
	strcpy(help, end_verz->directory);
	chdir(help);
	printf("Aktuelles Verzeichnis: %s", help);
	end_verz = help_ptr->previous;
	end_verz->next = NULL;
	free(help_ptr);
	return 0;
}
