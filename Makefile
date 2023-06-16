COMP  = gcc
APP = main

${APP}: ${APP}.c Authentication.h HidePassEnter.h TimeString.h
	${COMP} ${APP}.c -o diary

clear:
	rm ${APP}