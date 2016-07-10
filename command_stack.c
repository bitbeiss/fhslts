/*
 * command_stack.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */

#include "fhs_lite_shell.h"

//push() - Hinzufuegen eines Stack Elementes.
command* push(command *stack_ptr) {
	command *stack_ptr_help;
	stack_ptr_help = stack_ptr;
	
	//Neues Kommando Historien-Element anlegen.
	if ((stack_ptr = malloc(sizeof(command))) != NULL) {
		//Zeiger im neuen Element setzen.
		stack_ptr->previous = stack_ptr_help;
		stack_ptr->next = NULL;
		strcpy(stack_ptr->cmd,"\0");
		
		//next Zeiger im darunterliegenden Element aktualisieren.
		stack_ptr->previous->next = stack_ptr;
		
		//printw("\nnach push - stack_ptr: %p stack_ptr->next %p\n",stack_ptr,stack_ptr->next);
		return stack_ptr;
	}
	else {
		endwin();
		fprintf(stderr,OUT_OF_MEMORY_MESSAGE);
		exit(1);
		}
}

void show_stack(command *stack_ptr){
	//alle bisherigen (in Stack gespeicherten) Kommandos ausgeben.
	//entspricht einem "history"
	int i=0;
	printw("\n");
	stack_ptr = get_stack_bottom_pointer(stack_ptr);		//von unten her ausgeben
	while (stack_ptr->next != NULL) {
		printw("%i %s\n", i, (void *) stack_ptr->cmd);
		stack_ptr =  stack_ptr->next;
		i++;
	}
}

//Gibt den untersten Zeiger am Stack zurueck. (Element mit next Zeiger gleich NULL.)
command* get_stack_bottom_pointer(command *stack_ptr){
	while(stack_ptr->previous != NULL){
		stack_ptr = stack_ptr->previous;
		}
	return (stack_ptr);
	}


//Gibt den obersten Zeiger am Stack zurueck. (Element mit next Zeiger gleich NULL.)
command* get_stack_top_pointer(command *stack_ptr){
	while(stack_ptr->next != NULL){
		stack_ptr = stack_ptr->next;
		}
	return (stack_ptr);
	}

command *reuse(command *stack_ptr){
	//Wenn ein Befehl aus der Historie nochmals mit Return bestaetigt wird...
	
	command *stack_ptr_top;
	stack_ptr_top = get_stack_top_pointer(stack_ptr);
		
	//Neues Befehlselement "offiziell" oben auf den Stack legen.
	//Dabei wird dann das neue oberste  (leere) Element angelegt.

	strcpy(stack_ptr_top->cmd, stack_ptr->cmd);
	//stack_ptr = push(stack_ptr_top);
	stack_ptr = stack_ptr_top;
	return (stack_ptr);
}


int free_stack(command *stack_ptr){
	command *stack_ptr_help;
	
	//zum  Element gehen...
	stack_ptr = get_stack_top_pointer(stack_ptr);
	
	//Elemente von oben her aus dem Stapel entfernen/freigeben.
	for(;;){
		if(stack_ptr->previous != NULL) {
			stack_ptr_help = stack_ptr->previous;
			free(stack_ptr);
			stack_ptr = stack_ptr_help;
			}
		else {
			break;
		}
	//das erste Element noch aufraeumen, so der Pointer darauf
	//nicht NULL ist.
	if(stack_ptr != NULL) {
		free(stack_ptr);
		}
	}
	return 0;
	}
