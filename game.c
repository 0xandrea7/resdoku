#include "game.h"

void init_table(game *game){
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			game->table[i][j] = 0;
		}
	}
}

void print_table(game *game){
	for (int i = 0; i < ROWS; i++) {
		if (i % 3 == 0) printf(LINE);
		for (int j = 0; j < COLS; j++) {
			if (j % 3 == 0) printf(SEPARATOR);
			if (game->table[i][j] == 0) printf("%c", EMPTY_CHAR);
			else printf("%d", game->table[i][j]);
			if (j == COLS - 1) printf(SEPARATOR);
		}
		printf("\n");
		if (i == ROWS - 1) printf(LINE);
	}
	printf("\n");
}

int read_table_from_file(game *game, char *filename){
	FILE *fpnt = fopen(filename, "r");
	if (fpnt == NULL) return -1;

	char buff[4096];
	int cnt = 0;

	while (fgets(buff, 4096, fpnt) != NULL) {
		int len = strlen(buff);

		for (int i = 0; i < len; i++) {
			int row = cnt / ROWS;
			int col = cnt % COLS;

			if (buff[i] >= '0' && buff[i] <= '9' && cnt < ROWS * COLS) {
				game->table[row][col] = buff[i] - '0';
				cnt++;
			}
		}
	}
	fclose(fpnt); 
	return 1;
}

/* is_full returns 1 if the table is full */

int is_full(game *game){
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (game->table[i][j] == 0) return 0;
		}
	}
	return 1;
}

/* is_safe returns 1 if the move is safe */

int is_safe(game *game, int row, int col, int num){
	/* vertical check */

	for (int i = 0; i < ROWS; i++) {
		if (game->table[i][col] == num) return 0;
	}

	/* 	horizontal check */

	for (int i = 0; i < COLS; i++) {
		if (game->table[row][i] == num) return 0;
	}

	/* square check */

	int square_col = 0;
	int square_row = 0;

	if (col < 3) square_col = 0;
	else if (col < 6) square_col = 3;
	else square_col = 6;

	if (row < 3) square_row = 0;
	else if (row < 6) square_row = 3;
	else square_row = 6;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game->table[square_row + i][square_col + j] == num) return 0;
		}
	}

	return 1;
}

int backtracking_func(game *game, int row, int col){
	if (is_full(game)) return 1; 

	int new_col = (col + 1) % COLS;
	int new_row = (new_col == 0) ? (row + 1) : row;

	if (game->table[row][col] == 0) {
		for (int k = 1; k <= 9; k++) {
			if (is_safe(game, row, col, k) == 1) {
				game->table[row][col] = k;

				int check = backtracking_func(game, new_row, new_col);

				if (check == 1) return 1;

				game->table[row][col] = 0;
			}
		}
		return 0; 
	}
	else {
		return backtracking_func(game, new_row, new_col);
	}
}
