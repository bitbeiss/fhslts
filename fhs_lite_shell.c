/*
 * fhs_lite_shell.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */

#include "fhs_lite_shell.h"

//Globale Variablen initialisieren
SCREEN *console_term = NULL;

char cwd[CWDCHARS];

int main (int arcg, char *argv[]) {
	strcpy(cwd,"\0");

	if ((console_term = newterm("vt100",stdout,stdin)) == NULL) {
		endwin();
		fprintf(stderr,TERM_CREATE_MESSAGE);
		exit(1);
	}

	if (set_term(console_term) == NULL) {
		endwin();
		fprintf(stderr,TERM_SWITCH_MESSAGE);
		exit(1);
	}
	
	//Buffering deaktivieren
	if (cbreak() == ERR) {
		endwin();
		fprintf(stderr, BUFFER_DEACT_MESSAGE);
	   	exit(-7);
	}

	//Echo ausschalten
	if (noecho()) {
		endwin();
	  	fprintf(stderr,NOECHO_MESSAGE);
	    exit(-8);
	}

	//Terminalinhalt loeschen
	if (wclear(curscr)) {
		endwin();
		fprintf(stderr, CEAR_MESSAGE);
	 	exit(-9);
	}

	if (wrefresh(curscr)) {
		endwin();
		fprintf(stderr, REFRESH_MESSAGE);
	    exit(-10);
	}


	scrollok(stdscr, TRUE);

	//Instanz des Verzeichnispuffers fuer pushd und popd anlegen
	DIR_SAVE *verz_buff = NULL;
	if ((verz_buff = malloc(sizeof(DIR_SAVE))) != NULL) {
		//Verzeichnisbuffer initialisieren
		verz_buff->next = NULL;
		verz_buff->previous = NULL;
		verz_buff->directory[0] = '\0';
	}

	
	//Stackpointer Instanz anlegen
	command *stack_ptr = NULL;
	
	//Element am unteren Ende des Stack erzeugen.
	//bzw. Stack initialisieren
	if ((stack_ptr = malloc(sizeof(command))) != NULL) {
		//cmd initialisieren
		strcpy(stack_ptr->cmd,"\0");
		stack_ptr->previous = NULL;
		stack_ptr->next = NULL;
	}
	else {
		endwin();
		fprintf(stderr,OUT_OF_MEMORY_MESSAGE);
		exit(1);
	}
	
	//Tastatureingabe Zeichenweise abfragen.  
	keypad (stdscr, TRUE);
	noecho();
	printw("Welcome to fhs lite shell v.%s by Clemens J.Zuzan and Florian Hofinger.\n", FHSLTVERSION);
	printw("Have a lot of fun...\n");
	PROMPT
	
	//Endlosschleife, die die Tastatureingabe verarbeitet solange das Programm laeuft
	
	coords coo;
	coo.c=0;
	coo.x=0;
	coo.y=0;
	coo.i=0;

	while ((coo.c = getch ()) != 4) {
		stack_ptr = handle_key(coo.c,stack_ptr, verz_buff, &coo);
	}
	
	//aufraeumen
	endwin();
	free_stack(stack_ptr);
	return 0;
}
