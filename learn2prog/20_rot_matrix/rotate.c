
void rotate(char matrix[10][10]) {
    char rotate_matrix[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            rotate_matrix[i][j] = matrix[9 - j][i];
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matrix[i][j] = rotate_matrix[i][j];

        }

    }

}
