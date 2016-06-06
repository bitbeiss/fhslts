/*
 * help.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */

#include "fhs_lite_shell.h"

int run_help(int errorid){
	
		switch(errorid) {
			case 1: 	printw("ls <directory>\n");
				break;
			case 2: 	printw("cd <directory> or cd <..>\n");
				break;
			default:
				printw("\nInterne Funktionen:\n");
				printw("help\nfhstime\nfhsdate\necho\ncd\nls\n");
			} 
	return 0;
	}
