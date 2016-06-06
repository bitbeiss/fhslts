/*
 * fhs_lite_shell.c 
 * AUTHOR: Clemens J. Zuzan
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <curses.h>
#include <string.h>
#include <time.h>


#include <unistd.h>
int run_getcwd();
static char cwd[500];
#define PROMPT run_getcwd(); printw("%s>",cwd);

//Kommando Stack Element.
typedef struct Command{
	struct Command *next;
	struct Command *previous; 
	char cmd[80];
	} command;

//push() - hinzufuegen eines Stack Elementes.
command* push(command *stack_ptr) {
	command *stack_ptr_help = stack_ptr;
	
	//Neues Kommando historen Element anlegen.
	if ((stack_ptr = malloc(sizeof(command))) != NULL) {
		//Zeiger im neuen Element setzen.
		stack_ptr->previous = stack_ptr_help;
		stack_ptr->next = NULL;
		strcpy(stack_ptr->cmd,"\0");
		
		//next Zeiger im darunterliegenden Element aktualisieren.
		stack_ptr->previous->next = stack_ptr;
		
		return stack_ptr;
	}
	else {
		printf("Allozierung des Speichers fuer Kommandoelement fehlgeschlagen!\n");
		exit(1);
		}
}

void show_stack(command *stack_ptr){
	//alle bisherigen (in Stack gespeicherten) Kommandos ausgeben.
	while (stack_ptr->previous != NULL) {
		printw("\n%s\n", (void *) stack_ptr->cmd);
		stack_ptr =  stack_ptr->previous;
	}
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
	
	//command *stack_ptr_help;
	command *stack_ptr_top = get_stack_top_pointer(stack_ptr);
	
	/*
		if ((stack_ptr_help = malloc(sizeof(command))) != NULL) {
		
		//Kopieren der Inhalte in das neue Element.
		memcpy(stack_ptr_help,stack_ptr,sizeof(command));
		//Neues Element zu oberst auf den Stapel legen.
		stack_ptr_help->previous = stack_ptr_top;
		stack_ptr_top->next = stack_ptr_help;
		stack_ptr_help->next = NULL;
		*/
		
		//Neues Befehlselement offiziell oben auf den Stack legen.
		//Dabei wird dann das neue oberste  (leere) Element angelet.

		strcpy(stack_ptr_top->cmd, stack_ptr->cmd);
		stack_ptr = push(stack_ptr_top);
		//}
	/*
	else {
		printf("Allozierung des Speichers fuer Kommandoelement fehlgeschlagen!\n");
		exit(1);
	}*/
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
			stack_ptr=stack_ptr_help;
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

int run_fhsdate(){
	struct tm *tmnow;
	time_t tnow;
	time(&tnow);
	tmnow = localtime(&tnow);
	printw("\n%d.%d.%d\n",tmnow->tm_mday,tmnow->tm_mon +1, tmnow->tm_year + 1900);
	return 0;
	}

int run_fhstime(){
	time_t time1;
	struct tm *time2;
	char zeit[25];
	time1 = time(NULL);
	time2 = localtime(&time1);
	strcpy(zeit,asctime(time2));
	printw("\n%s\n",zeit);
	return 0;
	}

int run_echo(char *to_echo){
	printw("\n%s\n",to_echo);
	return 0;
	}
	
int run_help(){
	printw("\nInterne Funktionen:\n");
	printw("help\nfhstime\nfhsdate\necho\ncd\nls\n");
	return 0;
	}

int run_chdir(char *parameter){
	if (strcmp(parameter,"..")==0){
		system("cd ..");
	}
	else { 
		chdir(parameter);
	}
	return 0;
	}

int run_getcwd(){
    getcwd(cwd,sizeof(cwd));
    if (cwd==NULL) {
		fprintf(stderr, "Fehler bei getcwd Aufruf: %s\n", strerror(errno));
    } 
    else {
		return 0;
    }
    return -1;
}

int run_external_command(){
	return 0;
	}

int evaluate_expression(command *stack_ptr){
	//printw("\nEvaluating expression... %s\n",stack_ptr->cmd);
	
	
	char *ptr;
	char buffer[9][500];
	

	
	for(int i=0; i>10;i++){
		buffer[i][0]='\0';
	}

	//Delimiter hier ausschließlich "Leerzeichen"
	

	ptr = strtok(stack_ptr->cmd," ");
	//printw("\ncmd: %s, val:%s\n",stack_ptr->cmd,ptr);
	int i=0;
	while(ptr != NULL) {
		//printw("val:%s\n",ptr);
		strcpy(buffer[i],ptr);
		ptr = strtok(NULL," ");
		i++;
		if (i>=9) break;
		}

	//printw("buffer[0]=%s buffer[1]=%s",buffer[0],buffer[1]);
	
	
	if(strcmp(buffer[0],"help")==0){
		run_help();
		}
	else if(strcmp(buffer[0],"cd")==0){
		run_chdir(buffer[1]);
		}
	else if(strcmp(buffer[0],"fhsdate")==0){
		run_fhsdate();
		}
	else if(strcmp(buffer[0],"fhstime")==0){
		run_fhstime();
		}
	else if(strcmp(buffer[0],"echo")==0){
		run_echo(buffer[1]);
		}
	else{
		printw("\n");
		system(buffer[0]);
	}
	

	return 0;
}

int main (void) {
	
	//Stackpointer
	command *stack_ptr = NULL;
	//command *stack_ptr_tmp;
	
	//Element am unteren Ende des Stack erzeugen.
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
	int c=0, y=0, x=0, i=0;
	initscr ();      
	keypad (stdscr, TRUE);
	noecho();
	PROMPT
	while ((c = getch ()) != 4) {
		switch (c) {
			case KEY_DOWN:
				//printw("\n");
				//printw("KEY_DOWN: %d",c);
				if (stack_ptr->previous != NULL) {
					stack_ptr = stack_ptr->previous; 
					//Zeile loeschen
					getyx(stdscr, y, x);
					move(y, 0);
					clrtoeol();
					//Prompt und Kommando neu schreiben.
					PROMPT
					printw("%s",stack_ptr->cmd);
					//Positionszaehler auf momentane Position setzen.
					i=x;
				}
				else break;
				break;
				
			case KEY_UP:
				//printw("\n");
				//printw("KEY_UP: %d",c);
				if (stack_ptr->next != NULL) {
					stack_ptr = stack_ptr->next;
					//momentane Position in der shell ermitteln.
					getyx(stdscr, y, x);
					move(y, 0);
					clrtoeol(); // Zeile loeschen.
					//Prompt und Kommando neu schreiben.
					PROMPT
					printw("%s",stack_ptr->cmd);
					//Positionszaehler auf momentane Position setzen.
					i=x;
				}
				else break;
				break;
			case KEY_LEFT:
				getyx(stdscr, y, x);
				move(y, x-1);
				break;
			case KEY_RIGHT:
				getyx(stdscr, y, x);
				move(y, x+1);
				break;
			case KEY_BACKSPACE:
				//printw("\n");
				//printw ("KEY_BACKSPACE: %d",c);
				if (i>0) {
					i--;
					stack_ptr->cmd[i]='\0';
					getyx(stdscr, y, x);
					move(y, 0);
					clrtoeol();
					PROMPT
					printw("%s",stack_ptr->cmd);
				}
				else break;
				break;
			case 10: //KEY_ENTER 
				//Fall: Wir sind im Inneren des Stapels.
				//es handelt sich... eine Wiederverwendung...
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
				i=0;
				break;
			default:
				//printw ("Tastaturcode %d\n", c);
				stack_ptr->cmd[i]=c;
				stack_ptr->cmd[i+1]='\0';
				i++;
				
				getyx(stdscr, y, x);
				move(y, 0);
				clrtoeol();
				
				PROMPT
				printw("%s",stack_ptr->cmd);
				
		}		
	}
	
	endwin();
	free_stack(stack_ptr);
	return 0;
}
