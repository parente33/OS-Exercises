#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int **matrix) {
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void searchRow(int *row, int value, int rowIndex) {
    for (int j = 0; j < COLUMNS; j++) {
        if (row[j] == value) {
            printf("Value %d found in row %d, column %d\n", value, rowIndex, j);
            _exit(1);
        }
    }
    _exit(0);
}

// ex.5
int valueExists(int **matrix, int value) {
    pid_t pids[ROWS];
    int status;

    for (int i = 0; i < ROWS; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        if (!pids[i]) {
            searchRow(matrix[i],value,i);
        }
    }
    for (int i = 0; i < ROWS; i++) {
        waitpid(pids[i],&status,0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1) return 1;
    }

    return 0;
}


// ex.6
void linesWithValue(int **matrix, int value) {
    pid_t pids[ROWS];
    int status;
    int foundRows[ROWS];
    int foundCount = 0;

    for (int i = 0; i < ROWS; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        if (!pids[i]) {
            searchRow(matrix[i],value,i);
        }
    }
    for (int i = 0; i < ROWS; i++) {
        waitpid(pids[i],&status,0);
        if (WIFEXITED(status) && WEXITSTATUS(status) > 0) {
            foundRows[foundCount++] = WEXITSTATUS(status) - 1;
        }
    }
    if (foundCount > 0) {
        printf("Value %d found in rows: ", value);
        for (int i = 0; i < foundCount; i++) {
            printf("%d ", foundRows[i]);
        }
        printf("\n");
    } else {
        printf("Value %d was not found in the matrix\n", value);
    }
}