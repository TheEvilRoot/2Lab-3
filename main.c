#include <stdio.h>
#include <stdlib.h>

#include "CMatrixIO/matrixio.h"

#define true 1
#define false 0

typedef long long int HashCode;
typedef unsigned int boolean;

HashCode columnHash(int **matrix, int rows, int colIndex) {
    HashCode magic = 0x9e3779b1;
    HashCode hashCode = 0;

    for (int i = 0; i < rows; i++) {
        hashCode += matrix[i][colIndex] * magic;
    }

    return hashCode;
}

int ** createMatrix(int rows, int columns) {
    int **matrix = (int**) calloc(rows, sizeof(int*));

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *) calloc(columns, sizeof(int));
    }

    return matrix;
}

void printMatrix(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
}

void inflateGraph(const HashCode *hashes, int **map, boolean *valid, int columns) {
    for (int i = 0; i < columns; i++) {
        map[i][i] = 1;
        for (int j = i + 1; j < columns; j++) {
            if (hashes[i] == hashes[j]) {
                if (i != j) {
                    valid[i] = valid[j] = true;
                  //  printf("%d %d\n", i, j); // Debug to show pairs
                }
                map[i][j] = map[j][i] = true;
            }
        }
    }
}

char* enterString(const char* message) {
	char* str = (char*)calloc(1, sizeof(char)); // Checked
	if (str == NULL) {
		return NULL;
	}

	int i = 0;
	char c;

	printf("%s", message);

	fflush(stdin);
	fseek(stdin, 0, SEEK_END);
	while ((c = getchar()) != -1) {
		str[i++] = c;

		if (c == '\n') {
			str[i - 1] = '\0';
			break;
		}

		if (!(str = (char*)realloc(str, sizeof(char) * (i + 1)))) {
			break;
		}
	}

	return str;
}

int main() {
    unsigned int rows;
    unsigned int columns;

    int **matrix = readMatrix("C:/matrix.txt", &rows, &columns);

    if (matrix == NULL) {
      enterString("Matrix reading error\nEnter any symbol to exit the program...");
      return 1;
    }

    printMatrix(matrix, rows, columns);

    HashCode *hashes = (HashCode*) calloc(columns, sizeof(HashCode));
    for (int i = 0; i < columns; i++) {
        hashes[i] = columnHash(matrix, rows, i);
    }

    int **map = createMatrix(columns, columns);

    boolean *valid = (boolean*) calloc(columns, sizeof(boolean));
    boolean *visited = (boolean*) calloc(columns, sizeof(boolean));

    inflateGraph(hashes, map, valid, columns);
		
		boolean flag = false;

    for (int i = 0; i < columns; i++) {
        int isValid = !visited[i] && valid[i];

        if (isValid) {
            printf("Is similar: ");
						flag = true;
            for (int j = 0; j < columns; j++) {
                int isSimilar = map[i][j];

                if (isSimilar) {
                    visited[j] = true;
                    printf("%d ", j);
                }
            }
            printf("\n");
        }
    }

    if (!flag) {
			printf("No similar columns found\n");
    }

	enterString("Enter any symbol to exit the program...");
    return 0;
}
