COMP  = gcc
APP = main
EXEC = diary

${APP}: ${APP}.c Authentication.h HidePassEnter.h TimeString.h
	${COMP} ${APP}.c -o ${EXEC}

clear:
	rm ${EXEC}