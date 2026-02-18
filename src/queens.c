#include "queens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_queens(queens *q, int n) {
	q->buffer = (int *)malloc(n * n * sizeof(int));
	if (q->buffer != NULL) {
		q->queens_per_row = (int *)malloc(n * sizeof(int));
		if (q->queens_per_row == NULL) {
			dealloc_queens(q);
			printf("r");
			return;
		}
		q->queens_per_col = (int *)malloc(n * sizeof(int));
		if (q->queens_per_col == NULL) {
			dealloc_queens(q);
			printf("c");
			return;
		}
        q->num_queens = n;
		for (int i = 0; i < q->num_queens; i++) {
			q->buffer[i] = i;
			q->queens_per_col[i] = 1;
			if (i == 0) {
				q->queens_per_row[i] = q->num_queens;
			} else {
				q->queens_per_row[i] = 0;
			}
		}
    } else {
        q->num_queens = 0;
		printf("b");
    }
}

void dealloc_queens(queens *q) {
	if (q->buffer != NULL) {
        free(q->buffer);
        q->buffer = NULL;
    }
	if (q->queens_per_row != NULL) {
        free(q->queens_per_row);
        q->queens_per_row = NULL;
    }
	if (q->queens_per_col != NULL) {
        free(q->queens_per_col);
        q->queens_per_col = NULL;
    }
    q->num_queens = 0;
}

void move_queen(queens *q, int idx) {
	if (idx < 0 || idx >= q->num_queens) return;
	q->queens_per_row[q->buffer[idx] / q->num_queens]--;
	q->queens_per_col[q->buffer[idx] % q->num_queens]--;
	q->buffer[idx]++;
	if (q->buffer[idx] < q->num_queens * q->num_queens) {
		q->queens_per_row[q->buffer[idx] / q->num_queens]++;
		q->queens_per_col[q->buffer[idx] % q->num_queens]++;
	}
	for (int j = idx; j >= 0; j--) {
		if (q->buffer[j] >= q->num_queens * q->num_queens - (q->num_queens - j - 1)) {
			if (j > 0) {
				if (q->buffer[j - 1] < q->num_queens * q->num_queens) {
					q->queens_per_row[q->buffer[j - 1] / q->num_queens]--;
					q->queens_per_col[q->buffer[j - 1] % q->num_queens]--;
				}
				q->buffer[j - 1]++;
				if (q->buffer[j - 1] < q->num_queens * q->num_queens) {
					q->queens_per_row[q->buffer[j - 1] / q->num_queens]++;
					q->queens_per_col[q->buffer[j - 1] % q->num_queens]++;
				}
				for (int k = j; k < q->num_queens; k++) {
					if (q->buffer[k] < q->num_queens * q->num_queens) {
						q->queens_per_row[q->buffer[k] / q->num_queens]--;
						q->queens_per_col[q->buffer[k] % q->num_queens]--;
					}
					q->buffer[k] = q->buffer[j - 1] + 1 + k - j;
					if (q->buffer[k] < q->num_queens * q->num_queens) {
						q->queens_per_row[q->buffer[k] / q->num_queens]++;
						q->queens_per_col[q->buffer[k] % q->num_queens]++;
					}
				}
			}
		} else {
			break;
		}
	}
}

char is_valid_board(queens *q, char *board, int *regions) {
	for (int i = 0; i < 26; i++) {
		regions[i] = 0;
	}
	
	//check rook-style movement
	if (q->buffer == NULL || q->queens_per_row == NULL || q->queens_per_col == NULL) return 0;
	for (int i = 0; i < q->num_queens; i++) {
		if (q->queens_per_row[i] != 1 || q->queens_per_col[i] != 1) return 0;
	}
	
	//check king-style movement
	for (int i = 0; i < q->num_queens; i++) {
		regions[(int)board[q->buffer[i]] - 65]++;
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (q->buffer[i] + q->num_queens * j + k > 0 && q->buffer[i] + q->num_queens * j + k < q->num_queens * q->num_queens && !(j == 0 && k == 0)) {
					for (int l = 0; l < q->num_queens; l++) {
						if (q->buffer[l] == (q->buffer[i] / q->num_queens + j) * q->num_queens + q->buffer[i] % q->num_queens + k) return 0;
					}
				}
			}
		}
	}
	
	//check regions
	int num_unary_regions = 0;
	for (int i = 0; i < 26; i++) {
		if (regions[i] > 1) return 0;
		if (regions[i] == 1) num_unary_regions++;
	}
	if (num_unary_regions != q->num_queens) return 0;
	
	return 1;
}

void print_board(queens *q, char *board) {
	int cur_queen_idx = 0;
	for (int row = 0; row < q->num_queens; row++) {
		for (int col = 0; col < q->num_queens; col++) {
			if (q->buffer[cur_queen_idx] / q->num_queens == row && q->buffer[cur_queen_idx] % q->num_queens == col) {
				printf("#");
				cur_queen_idx++;
			} else {
				printf("%c", board[row * q->num_queens + col]);
			}
		}
		printf(" %d\n", q->queens_per_row[row]);
	}
	for (int col = 0; col < q->num_queens; col++) {
		printf("%d", q->queens_per_col[col]);
	}
}