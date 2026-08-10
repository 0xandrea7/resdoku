CC = gcc
CFLAGS = -Wall -Wextra

sudoku: main.c game.c game.h
	$(CC) $(CFLAGS) main.c game.c -o solver

clean:
	rm -f solver
