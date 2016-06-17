COMPILE: "make all" bzw "make clean" 
(Alles wird je nach Einstellung im makefile nach DEBUG oder RELEASE kompiliert.
Erzeugt wird ein Binary "fhslts" im DEBUG oder RELEASE Verzeichnis.)

Die Probleme mit "ncurses" Linkage wurden gelöst, die Lösung ist jetzt schon umgesetzt und auch das makefile
dahingehend korrigiert. Wichtig ist es zudem eine Version von curses zu installieren, die jünger als 2014 ist,
davor gibt es darin einen Bug, der den Start des stderr Terminals verhindert.
Das Programm ist aber noch immer voll mit anderen Fehlern.

