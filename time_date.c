/*
 * time_datae.c 
 * AUTHOR: Clemens J. Zuzan, Florian Hofinger
 * YEAR: 2016
 * PURPOSE: Implement a lightweight shell.
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * VERSION: 1.0
 * COMPILE: make
 */

#include "fhs_lite_shell.h"

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
