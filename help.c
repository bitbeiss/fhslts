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
			case LS_ERROR:
				printw("\nls <directory>\n");
				break;
			case CD_ERROR:
				printw("\ncd <directory> or cd <..>\n");
				break;
			case FHSDATE_ERROR:
				printw("\nfhsdate - gibt das aktuelle Datum im fhs-Format [TT:MM:JJJ] aus.\n");
				break;
			case FHSTIME_ERROR:
				printw("\nfhstime - gibt die aktuelle Zeit (und Datum) im fhs-Format [WeekDay Month TT hh:mm:ss] aus.\n");
				break;
			case HISTORY_ERROR:
				printw("\nhistory - listet alle bisher eingegebenen Befehle.\n");
				break;
			case ECHO_ERROR:
				printw("\necho - echo gibt die nach dem Kommando stehenden Zeichen 1:1 aus.\n");
				printw("Maximal koennen %i Argumente an echo uebergeben werden.\n",MAX_ECHO_BUFFER_ARGS);
				break;
			case PWD_ERROR:
				printw("\npwd - gibt das aktuelle Arbeitsverzeichnis aus.\n");
				break;
			case EXECUTE_ERROR:
				printw("\nexec <cmd> fuehrt ein Kommando in einer fork aus.\n");
				break;
			case PUSHD_ERROR:
				printw("\npushd - legt das aktuelle Arbeitsverzeichnis auf einen Stack. \
						\nMit popd koennen Verzeichnisse wieder vom Stack (LIFO) geholt werden.\n");
				break;
			case POPD_ERROR:
				printw("\npopd - holt ein Verzeichnis vom Verzeichnisstack.\
						\nMit pushd koennen Verzeichnisse auf diesem Stack (LIFO) abgelegt werden.\n");
				break;
			default:
				printw("\n\nInterne Funktionen:\n");
				printw("\nhelp <cmd> \
						\nfhstime \
						\nfhsdate  \
						\necho <what to echo> \
						\ncd <dir> \
						\nls <dir> \
						\nhistory \
		 				\npwd \
						\npushd \
						\npopd \
						\nexec <cmd> \
						\ncommand history --> use cursor keys up and down \
						\nquit\n");

			} 
	return 0;
	}
