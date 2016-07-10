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



//Speichert das aktuelle Verzeichnis in den Stack,
//Uebergabe Parameter ist der ptr auf das zuletzt gespeicherte Verzeichnis
int run_pushd(DIR_SAVE *verz_buff){
	char buffer[MAX_CHARS_PER_LINE];

	//zum obersten Element im Stack gehen
	verz_buff = get_top_pointer(verz_buff);

	DIR_SAVE *ptr_help = verz_buff;



	//Neues Verzeichnis-Element anlegen.
	if ((verz_buff = malloc(sizeof(DIR_SAVE))) != NULL) {
		//Zeiger im neuen Element setzen.
		verz_buff->previous = ptr_help;
		verz_buff->next = NULL;
		verz_buff->directory[0] = '\0';

		//Speichert aktuelles Verzeichnis.
		if(NULL != getcwd(buffer,80) ){
			strcpy(verz_buff->directory,buffer);
		}
		else {
			printw(DIR_MISSING_MESSAGE);
			return 1;
		}

		//"next" Zeiger im darunterliegenden Element aktualisieren.
		verz_buff->previous->next = verz_buff;

		printw(SAVED_DIR_MESSAGE);
		printw("%s\n",verz_buff->directory);
		return 0;
	}
	else {
		printw(OUT_OF_MEMORY_MESSAGE);
		return 1;
		}
}

//Wechselt in letztes gespeichertes Verzeichnis und loescht es aus dem Stack
//Uebergabe ist der ptr auf das letzte Verzeichnis
int run_popd(DIR_SAVE *verz_buff) {
	char help[MAX_CHARS_PER_LINE];
	help[0] = '\0';

	//zum obersten Element im Stack gehen
	verz_buff = get_top_pointer(verz_buff);

	//Nachsehen, ob noch ein Verzeichnis im Stack ist.
	if (verz_buff->previous==NULL) {
		printw(NO_MORE_DIR_IN_STACK_MESSAGE);
		return 1;
	}

	DIR_SAVE *help_ptr;
	help_ptr = verz_buff;
	strcpy(help, verz_buff->directory);
	//chdir(help);

	// Verzeichnis ausgeben
	printw("\n%s\n", help);
	verz_buff = help_ptr->previous;
	verz_buff->next = NULL;
	free(help_ptr);
	return 0;
}

DIR_SAVE *get_top_pointer(DIR_SAVE *verz_buff) {
	while (verz_buff->next!=NULL) {
		verz_buff = verz_buff->next;
		}
	return verz_buff;
	}

