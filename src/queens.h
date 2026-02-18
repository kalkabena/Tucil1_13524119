#ifndef QUEENS_H
#define QUEENS_H

#define MAX_BOARD_SIZE 100

typedef struct {
	int num_queens;
	int *buffer;
	int *queens_per_row;
	int *queens_per_col;
} queens;

void create_queens(queens *q, int n);

void dealloc_queens(queens *q);

void move_queen(queens *q, int idx);

char is_valid_board(queens *q, char *board, int *regions);

void print_board(queens *q, char *board);

#endif