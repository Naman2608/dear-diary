COMP  = gcc
APP = main
EXEC = diary

${APP}: ${APP}.c Authentication.h HidePassEnter.h TimeString.h TimeString.c Authentication.c help.c new.c open.c 
	${COMP} -c main.c TimeString.c Authentication.c help.c new.c open.c
	g++ -c randomD.cpp
	g++ main.o TimeString.o Authentication.o help.o new.o open.o randomD.o -o diary

clear:
	rm ${EXEC}