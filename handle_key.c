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
				getyx(stdscr, c->y0, c->x0);
				printw("%s",stack_ptr->cmd);
				//Positionszaehler auf momentane Position setzen.
				c->i=strlen(stack_ptr->cmd);
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
				getyx(stdscr, c->y0, c->x0);
				printw("%s",stack_ptr->cmd);
				//Positionszaehler auf momentane Position setzen.
				c->i=strlen(stack_ptr->cmd);
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

			getyx(stdscr, c->y, c->x);
			//printw("i:%i\n",c->i);
			if ( (c->i) > 0) {

				//Inhalt der Zeile ein Zeichen abzwacken
				//(c->i)--;
				//stack_ptr->cmd[(c->i)]='\0';

				//Zeile umschreiben/momentane pos auslassen.

				int len = c->i;
				int ii = 0;

				char cmd_tmp[MAX_CHARS_PER_LINE];
				//printw("c->i: %i\n",c->i);
				int j;
				for(j=0; j<=len; j++) {
					//printw("%c",stack_ptr->cmd[ii]);
					// Die derzeitige Position beim Umschreiben ueberspringen
					// (Vom Promptende aus gesehen im Kommando)
					if(j==abs(c->x0 - (c->x-1))){
						j++;
						c->i--;
					}
					cmd_tmp[ii] = stack_ptr->cmd[j];
					ii++;
				}
				strcpy(stack_ptr->cmd,cmd_tmp);

				//Zeile loeschen
				move(c->y, 0);
				clrtoeol();
				//Prompt neu aufbauen
				PROMPT
				printw("%s",stack_ptr->cmd);
				move(c->y,c->x-1);
			}
			else break;
			break;
				
		case KEY_ENTER_CUSTOM:
			if (verb==1) printw("KEY_ENTER_CUSTOM: %d\n",key);
			//Fall: next Zeiger am Stapel nicht Null: Wir sind im Inneren des Stapels.
			//es handelt sich... um eine Wiederverwendung eines Befehles durch den User!
			if (stack_ptr->next != NULL){
				if(verb==1) printw("reusing cmd...\n");

				//Kommando in den Speicher des obersten (leeren) Stackelements kopieren.
				stack_ptr = reuse(stack_ptr);
				if(verb==1) printw("executing cmd...\n");

				evaluate_expression(stack_ptr,verz_buff);
				//jetzt erst Push ausfuehren
				stack_ptr = push(stack_ptr);
			}
			else {
				if(verb==1) printw("Executing cmd on top of stack\n");
				//Fall: alles normal, sind oben am Stapel -
				//push-back durchfuehren....

				//Ausdruck auswerten
				if(verb==1) printw("Evaluating...\n");
				evaluate_expression(stack_ptr,verz_buff);

				//Ausdruck auf den Kommando Stack "ablegen" indem neues Kommando auf Spitze des Stack angelegt wird.
				//stack_ptr zeigt danach auf das neue (noch leere Kommando)
				stack_ptr = push(stack_ptr);
			}

			//Prompt leer wieder aufbauen.
			PROMPT
			//Position des Prompts sichern
			getyx(stdscr, c->y0, c->x0);
			//Positionszaehler auf leer zuruecksetzen.
			c->i=0;
			break;
				
		default:
			//Zeichen zu Kommandopuffer hinzufuegen (wenn keine Sondertaste)
			if (verb==1) printw ("Tastaturcode %d\n", key);
			//stack_ptr->cmd[(c->i)] = key;
			//stack_ptr->cmd[(c->i)+1] = '\0';
			getyx(stdscr, c->y, c->x);
			stack_ptr->cmd[(abs(c->x0 - c->x))] = key;
			//printw("\npos: %i, key: %c\n",(abs(c->x0 - c->x)), key);
			if((abs(c->x - c->x0) >= c->i )) {
				(c->i)++;
				stack_ptr->cmd[(c->i+1)] = '\0';
			}
			(c->x)++;
			move(c->y,c->x);


			//Bisher eingegebenes Kommando wieder aufbauen (nachdem der gedrueckte Key behandelt wurde.)
			//getyx(stdscr, c->y, c->x);
			move(c->y, 0);
			clrtoeol();
			if (verb==1) printw("\nBisher eingegebenes Kdo. wieder aufgebaut\n");
			PROMPT
			getyx(stdscr, c->y0, c->x0);
			printw("%s",stack_ptr->cmd);
			move(c->y,c->x);
	}

return stack_ptr;
}
