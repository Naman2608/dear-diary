
COMP  = gcc
APP = main

${APP}: ${APP}.c
	${COMP} ${APP}.c -o ${APP} 

clear: 
	rm ${APP}