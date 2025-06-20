#include "matrix.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <value to search>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int value = atoi(argv[1]);
    int **matrix = createMatrix();
    printMatrix(matrix);

    if(valueExists(matrix,value)) {
        printf("Value %d was found in the matrix\n", value);
    } else {
        printf("Value %d was not found in the matrix\n", value);
    }

    linesWithValue(matrix,value);

    freeMatrix(matrix);

    return 0;
}