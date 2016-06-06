#AUTHOR: Clemens J. Zuzan, Florian Hofinger
#PURPOSE: Makefile for fhslt fh-lighshell project.
#YEAR:	2016
#COMPILE: make

objects = fhs_lite_shell.o command_stack.o parser.o pushd_popd.o handle_key.o external_cmd.o time_date.o help.o directory_func.o echo.o

fhslt: $(objects)
		gcc -Wall -std=gnu99 -lncurses -o fhslt $(objects)

fhs_lite_shell.o: fhs_lite_shell.c fhs_lite_shell.h
		gcc -Wall -std=gnu99 -c fhs_lite_shell.c
		
command_stack.o: command_stack.c fhs_lite_shell.h
		gcc -Wall -std=gnu99 -c command_stack.c
		
parser.o: parser.c fhs_lite_shell.h
		gcc -Wall -std=gnu99 -c parser.c

pushd_popd.o: pushd_popd.c fhs_lite_shell.h
		gcc -Wall -std=gnu99 -c pushd_popd.c

handle_key.o: handle_key.c fhs_lite_shell.h
		gcc -Wall -std=gnu99 -c handle_key.c

external_cmd.o: external_cmd.c fhs_lite_shell.h
		gcc -Wall -std=gnu99 -c external_cmd.c

time_date.o: time_date.c fhs_lite_shell.h
		gcc -Wall -std=gnu99 -c time_date.c

help.o: help.c fhs_lite_shell.h
		gcc -Wall -std=gnu99 -c help.c

directory_func.o: directory_func.c fhs_lite_shell.h
		gcc -Wall -std=gnu99 -c directory_func.c

echo.o: echo.c fhs_lite_shell.h
		gcc -Wall -std=gnu99 -c echo.c

clean:
		rm fhslt $(objects)
