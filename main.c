#include <stdio.h>
#include "game.h"

int main(int argc, char *argv[]){
	if (argc != 2) {
		printf("Usage : %s <filename sudoku>\n", argv[0]);
		return -1;
	}

	game sudoku_board;

	if (read_table_from_file(&sudoku_board, argv[1]) == -1) {
		printf("Error : could not open or read %s\n", argv[1]);
		return -1;
	}
	print_table(&sudoku_board);

	backtracking_func(&sudoku_board, 0, 0);
	print_table(&sudoku_board);

	return 0;
}
