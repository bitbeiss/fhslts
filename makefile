#AUTHOR: Clemens J. Zuzan, Florian Hofinger
#PURPOSE: Makefile for fhslt fh-lighshell project.
#YEAR:	2016
#COMPILE: make



#Toggle compilation mode here!
mod=debug
#mode = release

ifeq ($(mod),debug)
	builddir=./DEBUG/
	mode=-ggdb
else
	builddir=./RELEASE/
	mode=-O3
endif

includedir=/usr/lib64/

objects=$(addprefix $(builddir), fhs_lite_shell.o command_stack.o parser.o pushd_popd.o handle_key.o \
	external_cmd.o time_date.o help.o directory_func.o echo.o )
	

$(builddir)fhs_lite_shell.o: fhs_lite_shell.c fhs_lite_shell.h
		gcc -Wall $(mode) -std=gnu99 -c fhs_lite_shell.c -o $(builddir)fhs_lite_shell.o -I$(includedir) -lcurses
		
$(builddir)command_stack.o: command_stack.c fhs_lite_shell.h
		gcc -Wall $(mode) -std=gnu99 -c command_stack.c -o $(builddir)command_stack.o -I$(includedir) -lcurses
		
$(builddir)parser.o: parser.c fhs_lite_shell.h
		gcc -Wall $(mode) -std=gnu99 -c parser.c -o $(builddir)parser.o

$(builddir)pushd_popd.o: pushd_popd.c fhs_lite_shell.h
		gcc -Wall $(mode) -std=gnu99 -c pushd_popd.c -o $(builddir)pushd_popd.o  $(builddir)fhs_lite_shell.o

$(builddir)handle_key.o: handle_key.c fhs_lite_shell.h
		gcc -Wall $(mode) -std=gnu99 -c handle_key.c -o $(builddir)handle_key.o -I$(includedir) -lcurses

$(builddir)external_cmd.o: external_cmd.c fhs_lite_shell.h
		gcc -Wall $(mode) -std=gnu99 -c external_cmd.c -o $(builddir)external_cmd.o

$(builddir)time_date.o: time_date.c fhs_lite_shell.h
		gcc -Wall $(mode) -std=gnu99 -c time_date.c -o $(builddir)time_date.o -I$(includedir) -lcurses

$(builddir)help.o: help.c fhs_lite_shell.h
		gcc -Wall $(mode) -std=gnu99 -c help.c -o $(builddir)help.o -I$(includedir) -lcurses

$(builddir)directory_func.o: directory_func.c fhs_lite_shell.h
		gcc -Wall $(mode) -std=gnu99 -c directory_func.c -o $(builddir)directory_func.o -I$(includedir) -lcurses  $(builddir)fhs_lite_shell.o

$(builddir)echo.o: echo.c fhs_lite_shell.h
		gcc -Wall $(mode) -std=gnu99 -c echo.c -o $(builddir)echo.o

fhslt: $(objects)
		gcc -Wall $(mode) -std=gnu99 -v -o $(builddir)fhslt  $(objects) -I$(includedir) -lcurses -ltinfo


all: fhslt 

clean:
		for object in $(objects); do \
			rm $$object; \
		done
		
		rm $(builddir)fhslt
