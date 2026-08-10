#include <stdio.h>
#include <string.h>

#define COLS 9
#define ROWS 9

#define EMPTY_CHAR 32 // ' '
#define LINE " -------------------\n"
#define SEPARATOR " | "

typedef struct Game {
	int table[ROWS][COLS];

} game;

void init_table(game *game);
void print_table(game *game);

int read_table_from_file(game *game, char *filename);

int is_full(game *game);
int is_safe(game *game, int row, int col, int num);

int backtracking_func(game *game, int row, int col);
