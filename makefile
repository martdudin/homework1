all:
	gcc -g -o homework1 -Wall -Wextra homework1.c info_manipulation.c

chatty:
	@echo Starting build
	gcc -o homework1 -Wall -Wextra homework1.c info_manipulation.c
	@echo Build finished

debug:
	gcc -g -o homework1 -Wall -Wextra homework1.c info_manipulation.c