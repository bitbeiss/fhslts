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

int run_echo(char *to_echo){
	printw("\n%s\n",to_echo);
	return 0;
	}
