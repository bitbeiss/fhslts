
COMPILE: "make all" bzw "make clean"; die ausfuehrbare Datei "fhslts" befindet sich dann in DEBUG oder RELEASE (je nach makefile-flag) 

ACHTUNG: bitte ein VERZEICHNIS "DEBUG" und "RELEASE" anlegen, wenn nicht vorhanden!
(Alles wird je nach Einstellung im makefile nach DEBUG oder RELEASE kompiliert.
Erzeugt wird ein Binary "fhslts" im DEBUG oder RELEASE Verzeichnis.)

ECLIPSE: Bei Verwendung des Projektes in Eclipse bitte als "makefile Projekt" importieren! 

BIBLIOTHEKEN: Die Ncurses/cureses Bibliothek muss manuell am System meist nachinstalliert werden.
Wichtig ist es, eine Version von curses zu installieren, die rezenter als 2014 ist,
davor gibt es darin einen Bug, der die Terminalgenerierung betrifft und ggf zu 
Fehlern beim Kompilieren fuehren kann.

SW TESTING: Die Shell wurde nur auf SuSE Linux und OSX letztgetestet, es sollten sich aber keine wesentlichen Differenzen zu
Ubuntu ergeben.

KNOWN BUGS: Momentan keine bekannt. (Version 1.1, 14 Juli 2016)

