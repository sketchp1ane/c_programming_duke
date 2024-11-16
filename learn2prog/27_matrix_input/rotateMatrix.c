#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

void rotate(char matrix[SIZE][SIZE]) {
    char temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[j][SIZE - 1 - i] = matrix[i][j];
        }
    }
    // Copy temp back to matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = temp[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    char matrix[SIZE][SIZE];

    if (argc != 2) {
        fprintf(stderr,"Usage: ./rotateMatrix inputFileName\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Could not open file\n");
        return EXIT_FAILURE;
    }

    char line[SIZE + 2] = {'\0'};
    int line_count = 0;


    while (fgets(line, SIZE + 2, file) != NULL) {

        if (line_count >= SIZE) {
            perror("The file is too long\n");
            return EXIT_FAILURE;
        }

        if (strchr(line, '\n') == NULL) {
            fprintf(stderr, "The line %d is too long\n", line_count + 1);
            return EXIT_FAILURE;
        }
        if (strlen(line) <= SIZE) {
            fprintf(stderr, "The line %d is too short\n", line_count + 1);
            return EXIT_FAILURE;
        }
        strncpy(matrix[line_count], line, SIZE);
        line_count++;



    }

    if (line_count < SIZE) {
        perror("The file is too short\n");
        return EXIT_FAILURE;
    }


    if (fclose(file) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
    }
    // Rotate the matrix 90 degrees clockwise
    rotate(matrix);

    // Print the rotated matrix to stdout
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            putchar(matrix[i][j]);
        }
        putchar('\n');
    }

    return EXIT_SUCCESS;
}
