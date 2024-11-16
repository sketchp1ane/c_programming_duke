#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void count(int *count_frequency, FILE *f) {
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (isalpha(c)) {
            char ch = tolower(c);
            count_frequency[ch - 'a']++;
        }
    }
}

void find_most_frequent(const int *count_frequency) {
    int max_index = 0;
    for (int i = 1; i < 26; i++) {
        if (count_frequency[max_index] < count_frequency[i]) {
            max_index = i;
        }
    }
    printf("%d\n", (max_index - ('e' - 'a') + 26) % 26);
}

int main(int argc, char **argv) {
    int count_frequency[26] = {0};
    if (argc != 2) {
        fprintf(stderr,"Usage: inputFileName\n");
        return EXIT_FAILURE;
    }

    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }

    count(count_frequency, f);

    find_most_frequent(count_frequency);

    if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;


}
