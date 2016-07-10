/*
 * echo.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */

#include "fhs_lite_shell.h"

int run_echo(char buffer[][MAX_CHARS_PER_LINE], int rows) {
	printw("\n");
	for(int i=1; i<(rows-2);i++){
		printw("%s ",buffer[i]);
	}
	printw("\n");
	return 0;
}
