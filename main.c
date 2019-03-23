#include <stdio.h>
#include <stdlib.h>

#define debug

typedef long long int HashCode;

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
            printf("[%d][%d]: ", i, j);
            matrix[i][j] = enterInt("");
        }
    }
}

int arrayEquals(int *array, int *qrray, int size) {
    for (int i = 0; i < size; i++){
        if (array[i] != qrray[i]) {
            return 0;
        }
    }
    return 1;
}

int validate(int *array, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i]) {
            count++;
        }

        if (count > 1) {
            return 1;
        }
    }
    return count > 1;
}

int main() {

#ifdef debug

#define R 4
#define C 8

    int rows = R;
    int columns = C;

    int **matrix = (int**) calloc(rows, sizeof(int*));

    int origin[R][C] = {
            {2,     7,      8,      5,      31,     4,      11,     6},
            {5,     4,      8,      12,     5,      11,     11,     31},
            {12,    11,     31,     4,     12,     7,      4,      2},
            {31,    11,     2,      2,      2,      11,     7,      8}
    };

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *) calloc(columns, sizeof(int));

        for (int j = 0; j < columns; j++) {
            matrix[i][j] = origin[i][j];
        }
    }
#else
    int rows = enterUnsigned("Enter number of rows: ");
    int columns = enterUnsigned("Enter number of columns");

    int **matrix = createMatrix(rows, columns);
    enterMatrix(matrix, rows, columns);
#endif

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }

    HashCode *hashes = (HashCode*) calloc(columns, sizeof(HashCode));
    for (int i = 0; i < columns; i++) {
        hashes[i] = columnHash(matrix, rows, i);
    }

    int **map = createMatrix(columns, columns);

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < columns; j++) {
            if (hashes[i] == hashes[j]) {
                 if (i != j) printf("%d %d\n", i, j);
                map[i][i] = map[i][j] = 1;
//                map[index][0] = min(i, j);
//                map[index][1] = max(i, j);
//
//                map = (int**) realloc(map, (++index + 1) * sizeof(int*));
//                map[index] = (int*) calloc(2, sizeof(int));
            }
        }
    }

    // 0 4
    // 0 3

    for (int i = 0; i < columns; i++) {
        int *entry = map[i];
        if (entry == NULL || !validate(entry, columns)) {
            map[i] = NULL;
            continue;
        }

        for (int j = 0; j < columns; j++) {
            if (j != i && map[j] != NULL) {
                if (arrayEquals(entry, map[j], columns)) {
                    map[j] = NULL;
                }
            }
        }

    }


    for (int i = 0; i < columns; i++) {
        if (map[i] != NULL) {
            printf("Is similar: ");
            for (int j = 0; j < columns; j++) {
                int isSimilar = map[i][j];

                if (isSimilar) {
                    printf("%2d", j);
                }
            }
            printf("\n");
        }
    }

    return 0;
}