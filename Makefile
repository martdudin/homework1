BIN = HW1_Mart_Dudin_212900MVEB
CFLAGS = -g -Wall -Wextra -Wconversion
CC = gcc

all: HW1_Mart_Dudin_212900MVEB.o HW1_Mart_Dudin_212900MVEB_2.o
	$(CC) -o $(BIN) HW1_Mart_Dudin_212900MVEB.o HW1_Mart_Dudin_212900MVEB_2.o