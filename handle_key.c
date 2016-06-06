/*
 * handle_key.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */

#include "fhs_lite_shell.h"

int handle_key(int key, command *stack_ptr, DIR_SAVE *end_verz, coords *c){
	
	switch (key) {
		case KEY_DOWN:
			//printw("KEY_DOWN: %d\n",c);
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
				
			//printw("KEY_UP: %d\n",c);
			if (stack_ptr->next != NULL) {
				stack_ptr = stack_ptr->next;
					
				//momentane Position in der shell ermitteln.
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
				getyx(stdscr, c->y, c->x);
				move(c->y, c->x-1);
				break;
			
			case KEY_RIGHT:
				getyx(stdscr, c->y, c->x);
				move(c->y, c->x+1);
				break;
			
			case KEY_BACKSPACE:
				//printw ("KEY_BACKSPACE: %d\n",c);
				if ( (c->i) > 0) {
					(c->i)--;
					stack_ptr->cmd[(c->i)]='\0';
					getyx(stdscr, c->y, c->x);
					move(c->y, 0);
					clrtoeol(); 
					PROMPT
					printw("%s",stack_ptr->cmd);
				}
				else break;
				break;
				
			case KEY_ENTER_CUSTOM:
				//Fall: Wir sind im Inneren des Stapels.
				//es handelt sich... um eine Wiederverwendung!
				if (stack_ptr->next != NULL){
					//Neues Element generieren, umkopieren,
					//oben auf Stapel ablegen
					stack_ptr = reuse(stack_ptr);
					}
				else {
					//Fall: alles normal, sind oben am Stapel -
					//push-back durchfuehren.
					strcat(stack_ptr->cmd,"\0");
					//Ausdruck auswerten
					evaluate_expression(stack_ptr);
					stack_ptr = push(stack_ptr);	
				}
							
				//Prompt leer wieder aufbauen.
				//printw("\n%s",stack_ptr->cmd);
				printw("\n"); 
				PROMPT
				
				//Positionszaehler zuruecksetzen.
				c->i=0;
				break;
				
			default:
				//printw ("Tastaturcode %d\n", c);
				stack_ptr->cmd[(c->i)]=c->c;
				stack_ptr->cmd[(c->i)+1]='\0';
				(c->i)++;
				
				getyx(stdscr, c->y, c->x);
				move(c->y, 0);
				clrtoeol();
				
				PROMPT
				printw("%s",stack_ptr->cmd);
				
		}
return 0;		
}
