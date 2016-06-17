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

//Globale Variablen
extern char cwd[500];
extern SCREEN *console_term;
extern SCREEN *stderr_term;


//Errorcodes
#define OUT_OF_MEMORY_ERROR 			(1)
#define UNKNOWN_DIRECTORY_ERROR			(2)
#define UNKNOWN_FILE_ERROR			(3)
#define FILE_OPEN_ERROR				(4)
#define FILE_CLOSE_ERROR			(5)

//Errormessages
#define OUT_OF_MEMORY_MESSAGE			"Error: Memory full!\n"
#define UNKNOWN_DIRECTORY_MESSAGE		"Error: Unknown directory\n"
#define	UNKNOWN_FILE_MESSAGE			"Error: File or path not valid!\n"
#define FILE_OPEN_MESSAGE			"Error: Could not open file!\n"
#define FILE_CLOSE_MESSAGE			"Error: Error encountered while closing file!\n"

//Zusaetzliche KEY_DEFINITIONEN
#define KEY_ENTER_CUSTOM 10

//Prompt Definition
#define PROMPT run_getcwd(); printw("%s>",cwd);


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
int run_popd(DIR_SAVE *);
int run_pushd(DIR_SAVE *);
int run_ls(char *);
int run_help(int );
int run_echo(char *);
int run_getcwd();
int run_chdir(char *);
int run_fhsdate();
int run_fhstime();
int evaluate_expression(command *);
int handle_key(int, command*, DIR_SAVE*, coords *coo);
int run_external_command(char*, char*[],int);

//Stackfunktionen
command* push(command *);
void show_stack(command *);
command *reuse(command *);
int free_stack(command *);

#endif
