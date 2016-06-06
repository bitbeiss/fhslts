/*
 * fhs_lite_shell.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make; gcc -std=gnu99 -Wall -o fhs_lite_shell fhs_lite_shell.c -lncurses
 */

#include "fhs_lite_shell.h"

int main (void) {
	
	
	stderr_term = newterm(NULL,stderr,stderr);
	console_term = newterm(NULL,stdin,stdout);
	
	set_term(console_term);
	
	//Instanz des Verzeichnispuffers fuer pushd und popd anlegen
	DIR_SAVE *end_verz = NULL;
	
	//Stackpointer Instanz anlegen
	command *stack_ptr = NULL;
	
	//Element am unteren Ende des Stack erzeugen.
	//bzw. Stack initialisieren
	if ((stack_ptr = malloc(sizeof(command))) != NULL) {
		strcpy(stack_ptr->cmd,"");
		stack_ptr->previous = NULL;
		stack_ptr->next = NULL;
	}
	else {
		printf("Allozierung des Speichers fuer Kommandoelement fehlgeschlagen!\n");
		exit(1);
	}
	
	//Tastatureingabe Zeichenweise abfragen.
	
	initscr();      
	keypad (stdscr, TRUE);
	noecho();
	PROMPT
	
	//Endlosschleife, die die Tastatureingabe verarbeitet solange das Programm laeuft
	
	
	coords coo;
	coo.c=0;
	coo.x=0;
	coo.y=0;
	coo.i=0;
	
	while ((coo.c = getch ()) != 4) {
		handle_key(coo.c,stack_ptr, end_verz, &coo);
	}
	
	set_term(console_term);
	endwin();
	set_term(stderr_term);
	endwin();
	free_stack(stack_ptr);
	return 0;
}
