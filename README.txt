COMPILE: "make all" bzw "make clean" 
ACHTUNG: bitte ein VERZEICHNIS "DEBUG" und "RELEASE" anlegen, wenn nicht vorhanden!
(Alles wird je nach Einstellung im makefile nach DEBUG oder RELEASE kompiliert.
Erzeugt wird ein Binary "fhslts" im DEBUG oder RELEASE Verzeichnis.)

Die Ncurses/cureses Bibliothek muss manuell am System meist nachinstalliert werden.
Wichtig ist es, eine Version von curses zu installieren, die rezenter als 2014 ist,
davor gibt es darin einen Bug, der die Terminalgenerierung betrifft und ggf zu 
Fehlern beim Kompilieren fuehren kann.

Die Shell wurde nur auf SuSE Linux letztgetestet, es sollten sich aber keine wesentlichen Differenzen zu
Ubuntu ergeben.

Bugs: fhsdate und fhstime funktionieren momentan leider nicht. (Segmentation fault.)

