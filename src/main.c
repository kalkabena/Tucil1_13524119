#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include "queens.h"

int main() {
	int bsz = 0;
	queens q;
	FILE *inptr;
	char board[MAX_BOARD_SIZE * MAX_BOARD_SIZE] = {0};
	char iter_str[MAX_BOARD_SIZE] = {0};
	char in_str[100];
	char temp[200];
	int regions[26];
	int dump;
	
	//system("cls");
	
	printf("Enter absolute file path, or q to quit > ");
	scanf("%s", in_str);
	if (strcmp(in_str, "q") == 0) return 0;
	
	int counter = 0;
	for (int i = 0; i < strlen(in_str); i++) {
		if (in_str[i] == '\\') {
			temp[counter] = '\\';
			counter++;
			temp[counter] = '\\';
		} else {
			temp[counter] = in_str[i];
		}
		counter++;
	}
	temp[counter] = '\0';
	
	inptr = fopen(temp, "r");
	
	char flag = 0;
	while (flag != 1) {
		memset(board, 0, sizeof(board));
		for (int i = 0; i < 26; i++) {
			regions[i] = 0;
		}
		if (flag == 2) {
			printf("Input board isn't square\n");
			printf("Enter absolute file path, or q to quit > ");
			scanf("%s", in_str);
			if (strcmp(in_str, "q") == 0) return 0;
			counter = 0;
			for (int i = 0; i < strlen(in_str); i++) {
				if (in_str[i] == '\\') {
					temp[counter] = '\\';
					counter++;
					temp[counter] = '\\';
				} else {
					temp[counter] = in_str[i];
				}
				counter++;
			}
			temp[counter] = '\0';
			inptr = fopen(temp, "r");
		}
		
		if (flag == 3) {
			printf("Input board contains invalid characters\n");
			printf("Enter absolute file path, or q to quit > ");
			scanf("%s", in_str);
			if (strcmp(in_str, "q") == 0) return 0;
			counter = 0;
			for (int i = 0; i < strlen(in_str); i++) {
				if (in_str[i] == '\\') {
					temp[counter] = '\\';
					counter++;
					temp[counter] = '\\';
				} else {
					temp[counter] = in_str[i];
				}
				counter++;
			}
			temp[counter] = '\0';
			inptr = fopen(temp, "r");
		}
		
		if (flag == 4) {
			printf("Input board doesn't contains the same number of regions as rows or cols\n");
			printf("Enter absolute file path, or q to quit > ");
			scanf("%s", in_str);
			if (strcmp(in_str, "q") == 0) return 0;
			counter = 0;
			for (int i = 0; i < strlen(in_str); i++) {
				if (in_str[i] == '\\') {
					temp[counter] = '\\';
					counter++;
					temp[counter] = '\\';
				} else {
					temp[counter] = in_str[i];
				}
				counter++;
			}
			temp[counter] = '\0';
			inptr = fopen(temp, "r");
		}
		
		while (inptr == NULL) {
			printf("file read failed\n");
			printf("Enter absolute file path, or q to quit > ");
			scanf("%s", in_str);
			if (strcmp(in_str, "q") == 0) return 0;
			counter = 0;
			for (int i = 0; i < strlen(in_str); i++) {
				if (in_str[i] == '\\') {
					temp[counter] = '\\';
					counter++;
					temp[counter] = '\\';
				} else {
					temp[counter] = in_str[i];
				}
				counter++;
			}
			temp[counter] = '\0';
			inptr = fopen(temp, "r");
		}
		
		flag = 1;
		int cols = 0;
		fgets(iter_str, MAX_BOARD_SIZE, inptr);
		bsz = strlen(iter_str);
		if (iter_str[bsz - 1] == '\n') {
			iter_str[bsz - 1] = '\0';
			bsz--;
		}
		for (int i = 0; i < bsz; i++) {
			if (iter_str[i] > 90 || iter_str[i] < 65) {
				flag = 3;
				break;
			} else {
				regions[iter_str[i] - 65]++;
			}
		}
		strncat(board, iter_str, bsz);
		cols++;
		while (fgets(iter_str, MAX_BOARD_SIZE, inptr) && flag != 3) {
			int temp_len = strlen(iter_str);
			if (iter_str[temp_len - 1] == '\n') {
				iter_str[temp_len - 1] = '\0';
				temp_len--;
			}
			if (bsz != temp_len) {
				flag == 2;
				break;
			}
			for (int i = 0; i < bsz; i++) {
				if (iter_str[i] > 90 || iter_str[i] < 65) {
					flag = 3;
					break;
				} else {
					regions[iter_str[i] - 65]++;
				}
			}
			if (flag == 3) break;
			strncat(board, iter_str, bsz);
			cols++;
		}
		if (cols != bsz) flag = 2;
		int num_regions = 0;
		for (int i = 0; i < 26; i++) {
			if (regions[i] > 0) num_regions++;
		}
		if (num_regions != bsz) flag = 4;
		fclose(inptr);
	}
	for (int i = 0; i < 26; i++) {
		regions[i] = 0;
	}
	
	//system("cls");
	printf("Regions:\n");
	for (int i = 0; i < bsz; i++) {
		for (int j = 0; j < bsz; j++) {
			printf("%c", board[i * bsz + j]);
		}
		printf("\n");
	}
	printf("\n\033[%dE", bsz);
	
	create_queens(&q, bsz);
	int cases = 1;
	
	auto t1 = std::chrono::steady_clock::now();
	char state = 0;
	while (q.buffer[0] < q.num_queens * (q.num_queens - 1)) {
		cases++;
		printf("\033[%dF", q.num_queens);
		move_queen(&q, q.num_queens - 1);
		if (is_valid_board(&q, board, regions) == 1) {
			printf("\033[32m");
		} else {
			printf("\033[39m");
		}
		print_board(&q, board);
		if (is_valid_board(&q, board, regions) == 1) {
			state = 1;
			break;
		}
	}
	auto t2 = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    printf("\033[0m\nWaktu: %d ms\n", elapsed_ms.count());
	printf("Kasus: %d\n", cases);
	if (state == 0) {
		printf("Tidak ada posisi valid\n");
		return 0;
	};
	printf("Apakah kamu ingin menyimpan hasil ini?(Y/N) > ");
	while ((dump = getchar()) != '\n' && dump != EOF);
	char yn;
	scanf("%c", &yn);
	while (!(yn == 'y' || yn == 'Y' || yn == 'n' || yn == 'N')) {
		printf("Invalid Input\n");
		printf("Apakah kamu ingin menyimpan hasil ini?(Y/N) > ");
		while ((dump = getchar()) != '\n' && dump != EOF);
		scanf("%c", yn);
	}
	if (yn == 'y' || yn == 'Y') {
		FILE *outptr;
		outptr = fopen("output", "w");
		counter = 0;
		if (outptr != NULL) {
			for (int i = 0; i < bsz; i++) {
				for (int j = 0; j < bsz; j++) {
					if (q.buffer[counter] == i * bsz + j) {
						fprintf(outptr, "#");
						counter++;
					} else {
						fprintf(outptr, "%c", board[i * bsz + j]);
					}
				}
				fprintf(outptr, "\n");
			}
			fclose(outptr);
			printf("Output file written at \\bin");
		} else {
			printf("output failed\n");
		}
	}
	
	dealloc_queens(&q);
	return 0;

}
