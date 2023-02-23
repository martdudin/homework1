all:
	gcc -g -o homework1 -Wall -Wextra homework1.c read_info.c

chatty:
	@echo Starting build
	gcc -o homework1 -Wall -Wextra homework1.c read_info.c
	@echo Build finished

debug:
	gcc -g -o homework1 -Wall -Wextra homework1.c read_info.c