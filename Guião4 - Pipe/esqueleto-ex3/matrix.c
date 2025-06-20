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

void lookupNumber(int** matrix, int value, int* vector){
    int pipes[ROWS][2]; // um pipe por linha

    for (int i = 0; i < ROWS; i++) {
        int pp = pipe(pipes[i]);
        if (pp < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        pid_t f = fork();
        if (f < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (!f) {
            close(pipes[i][0]);
            Minfo info;
            info.line_nr = i;
            info.ocur_nr = 0;

            for (int j = 0; j < COLUMNS; j++) {
                if (matrix[i][j] == value) info.ocur_nr++;
            }

            write(pipes[i][1],&info,sizeof(Minfo));
            close(pipes[i][1]);
            _exit(0);
        } else {
            close(pipes[i][1]); // processo pai só lê
        }
    }

    for (int i = 0; i < ROWS; i++) {
        Minfo info;
        read(pipes[i][0],&info,sizeof(Minfo));
        vector[info.line_nr] = info.ocur_nr;
        close(pipes[i][0]);
    }

    for (int i = 0; i < ROWS; i++) wait(NULL);
}