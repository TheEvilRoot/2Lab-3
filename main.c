#include <stdio.h>
#include <stdlib.h>

#define debug
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

unsigned int enterUnsigned(const char *message) {
    int ret = -1;

    do {
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
        printf("%s", message);
    } while (!scanf("%d", &ret) || ret < 0);

    return (unsigned  int) ret;
}


int enterInt(const char *message) {
    int ret = 0;

    do {
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
        printf("%s", message);
    } while (!scanf("%d", &ret));

    return ret;
}

int ** createMatrix(int rows, int columns) {
    int **matrix = (int**) calloc(rows, sizeof(int*));

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *) calloc(columns, sizeof(int));
    }

    return matrix;
}

void enterMatrix(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("matrix[%d][%d] = ", i, j);
            matrix[i][j] = enterInt("");
        }
    }
}

void printMatrix(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
}

void inflateHashes(const HashCode *hashes, int **map, boolean *valid, int columns) {
    for (int i = 0; i < columns; i++) {
        map[i][i] = 1;
        for (int j = i + 1; j < columns; j++) {
            if (hashes[i] == hashes[j]) {
                if (i != j) {
                    valid[i] = valid[j] = true;
                  //  printf("%d %d\n", i, j);
                }
                map[i][j] = map[j][i] = true;
            }
        }
    }
}

int main() {

#ifdef debug

#define R 4
#define C 8

    unsigned int rows = R;
    unsigned int columns = C;

    int **matrix = (int**) calloc(rows, sizeof(int*));

    int origin[R][C] = {
            {2,     7,      2,      5,      31,     4,      11,     12},
            {5,     4,      31,      12,     5,      11,     11,     31},
            {12,    11,     12,     4,     12,     7,      4,      2},
            {31,    11,     5,      2,      2,      11,     7,      5}
    };

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *) calloc(columns, sizeof(int));

        for (int j = 0; j < columns; j++) {
            matrix[i][j] = origin[i][j];
        }
    }
#else
    unsigned int rows = enterUnsigned("Enter number of rows: ");
    unsigned int columns = enterUnsigned("Enter number of columns");

    int **matrix = createMatrix(rows, columns);
    enterMatrix(matrix, rows, columns);
#endif

    printMatrix(matrix, rows, columns);

    HashCode *hashes = (HashCode*) calloc(columns, sizeof(HashCode));
    for (int i = 0; i < columns; i++) {
        hashes[i] = columnHash(matrix, rows, i);
    }

    int **map = createMatrix(columns, columns);

    boolean *valid = (boolean*) calloc(columns, sizeof(boolean));
    boolean *visited = (boolean*) calloc(columns, sizeof(boolean));

    inflateHashes(hashes, map, valid, columns);

    for (int i = 0; i < columns; i++) {
        int isValid = !visited[i] && valid[i];

        if (isValid) {
            printf("Is similar: ");

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

    return 0;
}