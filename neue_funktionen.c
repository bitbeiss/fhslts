/*
 * neue_funktionen.c
 *
 *  Created on: 23. Mai 2016
 *      Author: cyberfips
 */

/*Hallo!
Hier sind die Sachen, die ich geschrieben habe zum implementieren in die shell für BTS.

als erstes wird ein neues globales Struct benötigt: */

typedef struct dir_save{
	char directory[80];
	struct dir_save *next;
	struct dir_save *previous;
} DIR_SAVE;
DIR_SAVE *end_verz;


//dann die Funktionen:

//zeigt aktuelles Verzeichnis an
int run_pwd(){

	int size = 256;
	char wd[size];

	if(NULL != getcwd(wd,size))
		printf("\nArbeitsverzeichnis: %s\n",wd);
}

//speichert das aktuelle Verzeichnis in den Stack, Übergabe ist der ptr auf das zuletzt gespeicherte Verzeichnis
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
	char *help;
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

//damit lässt sich ein externes commando ausführen - Übergabe ist getokenizder String inkl. Kommando + Argumente
int run_external_command(char *command){


	pid_t process_id, waitprocess_id;
	int exec_ok;
	int status;
	process_id = fork();
	if (process_id == 0)
	{
		exec_ok = execvp(command[0], command[1]);  //erste Übergabe ist das Kommando, 2. Übergabe sind die Argumente
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

// in der evaluate_expression Funktion kommen folgende Dinge hinzu:

        else if(strcmp(buffer[0], "exit") == 0){		//beendet Shell bei eingabe von exit
		exit(0);
	}
	else if(strcmp(buffer[0], "pwd") == 0){			//zeigt aktuelles Arbeitsverzeichnis an
		run_pwd();
		}
	else if(strcmp(buffer[0], "popd") == 0){		//wechselt in letztes gespeichertes Verzeichnis, Übergabe ist ptr auf zuletzt gesp. Verzeichnis
		run_popd(end_verz);
	}
	else if(strcmp(buffer[0], "pushd") == 0){		//speichert aktuelles Verzeichnis, Übergabe ist ptr auf zuletz gespeichertes Verzeichnis
		run_pushd(end_verz);
	}
	else{
		run_external_command(buffer);		   //hier muss der komplette buffer übergeben werden(Kommando + Argumente)
	}
	return 0;
}

// leider kann ich die Funktionen noch nicht testen, da die befehle irgendwie nicht erkannt werden...
// da ich mich mit deiner Argument-Übergabe noch nicht wirklich auskenne, bitte ich dich die Übergabe-Parameter und so anzupassen
// LG Flo
