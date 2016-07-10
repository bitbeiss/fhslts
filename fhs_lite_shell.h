/*
 * fhs_lite_shell.h
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
*/

#ifndef FHSLT
#define FHSLT fhslt
#define FHSLTVERSION "1.1"

//External libraries
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <dirent.h>
#include <unistd.h>

//Globale Parameter
//max. Anzahl an Parametern zusaetzlich zum Befehl
#define MAX_PARAMETERS (9)
//max. Anzahl der Zeichen, die in einem Pfad vorkommen koennen/duerfen.
#define MAX_CHARS_PER_LINE 500
//max. Argumente, die an echo uebergeben werden koennen/duerfen.
//Achtung: zu hohe Angabe kann zu Segmentation Fault fuehren!
#define MAX_ECHO_BUFFER_ARGS 20

//Globale Variablen
extern char cwd[500];
extern SCREEN *console_term;

//Konstanten
#define MAX_LEN_CWD	1000

//Errorcodes
#define OUT_OF_MEMORY_ERROR 			(1)
#define UNKNOWN_DIRECTORY_ERROR			(2)
#define UNKNOWN_FILE_ERROR				(3)
#define FILE_OPEN_ERROR					(4)
#define FILE_CLOSE_ERROR				(5)
#define TERM_CREATE_ERROR				(6)

#define TERM_SWITCH_ERROR				(7)
#define BUFFER_DEACT_ERROR				(8)
#define NOECHO_ERROR					(9)
#define CLEAR_ERROR						(10)
#define REFRESH_ERROR					(11)

#define LS_ERROR						(12)
#define CD_ERROR						(13)
#define FHSDATE_ERROR					(14)
#define FHSTIME_ERROR					(15)
#define HISTORY_ERROR					(16)
#define	ECHO_ERROR						(17)
#define PWD_ERROR						(18)
#define EXECUTE_ERROR					(19)
#define PUSHD_ERROR						(20)
#define POPD_ERROR						(21)

//Fehlermeldungen allgemein (stack etc.)
#define OUT_OF_MEMORY_MESSAGE			"\nError: Memory full!\n"

//Fehlermeldungen Dateien
#define UNKNOWN_DIRECTORY_MESSAGE		"\nError: Unknown directory.\n"
#define	UNKNOWN_FILE_MESSAGE			"\nError: File or path not valid.\n"
#define FILE_OPEN_MESSAGE				"\nError: Could not open file or directory.\n"
#define FILE_CLOSE_MESSAGE				"\nError: Error encountered while closing file.\n"
#define FILE_EXISTS_BUT_NOT_DIR_MESSAGE "\nError: File exists but is not a directory.\n"
#define GET_CWD_MESSAGE					"\nError: Error encountered calling cwd.\n"

// Fehlermeldungen, die den Terminal betreffen
#define TERM_CREATE_MESSAGE				"\nError: Error encountered while creatin ncurses terminal.\n"
#define TERM_SWITCH_MESSAGE				"\nError: Error while switching to terminal.\n"
#define BUFFER_DEACT_MESSAGE			"\nError: cbreak returned error.\n"
#define NOECHO_MESSAGE					"\nError: noecho returned error.\n"
#define CEAR_MESSAGE					"\nError: clear returned error.\n"
#define REFRESH_MESSAGE					"\nError: refresh returned error.\n"

// Fehlermeldungen, die den Verzeichnisstack betreffen
#define DIR_MISSING_MESSAGE				"\nError: could not find directory.\n"
#define NO_MORE_DIR_IN_STACK_MESSAGE	"\nError: no directory left in stack.\n"

// Hinweise, ohne dass es sich um Fehler handelt.
#define SAVED_DIR_MESSAGE "\nMessage: Saved directory to stack:"

//Zusaetzliche KEY_DEFINITIONEN
#define KEY_ENTER_CUSTOM 10
#define KEY_BACKSPACE_LINUX 127

//Prompt Definition
#define PROMPT run_getcwd(); printw(">");

//------------------------------------
//Datenstrukturen

//Kommando-Stack-Element Zeiger.
typedef struct Command{
	struct Command *next;
	struct Command *previous; 
	char cmd[80];
	} command;

//DIR_SAVE struktur fuer popd und pushd
typedef struct dir_save{
     char directory[80];
     struct dir_save *next;
     struct dir_save *previous;
} DIR_SAVE;

DIR_SAVE *end_verz;

//Verschiedene Koordinaten und Zaehler des Terminals in Stuktur zusammengefasst.
typedef struct Coords {
	int c;
	int y;
	int x;
	int i;
	} coords;

//------------------------------------
//Funktionsprototypen

//Verzeichnisstackfunktionen
DIR_SAVE *get_top_pointer(DIR_SAVE *);
int run_popd(DIR_SAVE *);
int run_pushd(DIR_SAVE *);


//Allg. interne Shell Funktionen
int run_ls(char *);
int run_help(int );
int run_echo(char [][MAX_CHARS_PER_LINE], int);
int run_getcwd();
int run_chdir(char *);
int run_fhsdate();
int run_fhstime();
int run_external_command(char*, char*[],int);

//Funktionen hinter den Kulissen
int evaluate_expression(command *, DIR_SAVE *);
command* handle_key(int, command*, DIR_SAVE*, coords *coo);

//Stackfunktionen
command* push(command *);
void show_stack(command *);
command *reuse(command *);
int free_stack(command *);
command* get_stack_bottom_pointer(command *stack_ptr);
command* get_stack_top_pointer(command *stack_ptr);

#endif
