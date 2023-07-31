COMP  = gcc
APP = main
EXEC = diary

${APP}: ${APP}.c Authentication.h HidePassEnter.h TimeString.h TimeString.c Authentication.c help.c new.c open.c 
	${COMP} ${APP}.c -o ${EXEC} TimeString.c Authentication.c help.c new.c open.c 

clear:
	rm ${EXEC}