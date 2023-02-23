all:
	gcc -o homework1 -Wall -Wextra homework1.c read_info.c argp.c

chatty:
	@echo Starting build
	gcc -o homework1 -Wall -Wextra homework1.c read_info.c argp.c
	@echo Build finished

no_argp:
	gcc -o homework1 -Wall -Wextra homework1.c read_info.c