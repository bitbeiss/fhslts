/*
 * handle_key.c 
 *
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * 			Handle one keystroke at a time and receive/store completed lines.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */

#include "fhs_lite_shell.h"



command * handle_key(int key, command *stack_ptr, DIR_SAVE *verz_buff, coords *c){
	int verb = 0;
	switch (key) {
		case KEY_DOWN:
			if (verb==1) printw("KEY_DOWN: %d\n",key);
			if (stack_ptr->previous != NULL) {
				stack_ptr = stack_ptr->previous; 
					
				//Zeile loeschen
				getyx(stdscr, c->y, c->x);
				move(c->y, 0);
				clrtoeol();
					
				//Prompt und Kommando neu schreiben.
				PROMPT
				printw("%s",stack_ptr->cmd);
				//Positionszaehler auf momentane Position setzen.
				c->i=c->x;
			}
			else break;
			break;
				
		case KEY_UP:
			if (verb==1) printw("KEY_UP: %d\n",key);
			if (stack_ptr->next != NULL) {
				stack_ptr = stack_ptr->next;
					
				//momentane Position in der Shell ermitteln.
				getyx(stdscr, c->y, c->x);
				move(c->y, 0);
				clrtoeol(); // Zeile loeschen.
					
				//Prompt und Kommando neu schreiben.
				PROMPT
				printw("%s",stack_ptr->cmd);
				//Positionszaehler auf momentane Position setzen.
				c->i=c->x;
			}
			else break;
			break;
			
		case KEY_LEFT:
			if (verb==1) printw("KEY_LEFT: %d\n",key);
			getyx(stdscr, c->y, c->x);
			move(c->y, c->x-1);
			break;

		case KEY_RIGHT:
			if (verb==1) printw("KEY_RIGHT: %d\n",key);
			getyx(stdscr, c->y, c->x);
			move(c->y, c->x+1);
			break;
			
		case KEY_BACKSPACE_LINUX:
			if (verb==1) printw ("KEY_BACKSPACE: %d\n",key);
			if ( (c->i) > 0) {
				(c->i)--;
				//inhalt der Zeile ein Zeichen abzwacken
				stack_ptr->cmd[(c->i)]='\0';
				getyx(stdscr, c->y, c->x);
				//Zeile loeschen
				move(c->y, 0);
				clrtoeol();
				//Prompt neu aufbauen
				PROMPT
				printw("%s",stack_ptr->cmd);
			}
			else break;
			break;
				
		case KEY_ENTER_CUSTOM:
			if (verb==1) printw("KEY_ENTER_CUSTOM: %d\n",key);
			//Fall: next Zeiger am Stapel nicht Null: Wir sind im Inneren des Stapels.
			//es handelt sich... um eine Wiederverwendung eines Befehles durch den User!
			if (stack_ptr->next != NULL){
				if(verb==1) printw("reusing cmd...\n");
				stack_ptr = reuse(stack_ptr);
				if(verb==1) printw("executing cmd...\n");
				evaluate_expression(stack_ptr,verz_buff);
				stack_ptr = push(stack_ptr);
			}
			else {
				if(verb==1) printw("Executing cmd on top of stack\n");
				//Fall: alles normal, sind oben am Stapel -
				//push-back durchfuehren....

				//Ausdruck auswerten
				if(verb==1) printw("Evaluating...\n");
				//printw("\nKommando derzeit: %s\n",stack_ptr->cmd);

				evaluate_expression(stack_ptr,verz_buff);

				//Ausdruck auf den Kommando Stack "ablegen" indem neues Kommando auf Spitze des Stack angelegt wird.
				//stack_ptr zeigt danach auf das neue (noch leere Kommando)
				stack_ptr = push(stack_ptr);
			}

			//Prompt leer wieder aufbauen.
			PROMPT
			//Positionszaehler zuruecksetzen.
			c->i=0;
			break;
				
		default:
			//Zeichen zu Kommandopuffer hinzufuegen (wenn keine Sondertaste)
			if (verb==1) printw ("Tastaturcode %d\n", key);
			stack_ptr->cmd[(c->i)] = key;
			stack_ptr->cmd[(c->i)+1] = '\0';
			(c->i)++;

			//Bisher eingegebenes Kommando wieder aufbauen (nachdem der gedrueckte Key behandelt wurde.)
			getyx(stdscr, c->y, c->x);
			move(c->y, 0);
			clrtoeol();
			if (verb==1) printw("\nBisher eingegebenes Kdo. wieder aufgebaut\n");
			PROMPT
			printw("%s",stack_ptr->cmd);
	}

return stack_ptr;
}
