#include <stdio.h>

size_t maxSeq(int * array, size_t n) {
    if (array == NULL || n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    size_t counter = 1;
    size_t max = 1;

    for (int i = 1; i < n; i++) {
        if (*(array + i) > *(array + i - 1)) {
            counter++;
            if (counter > max) {
                max = counter;
            }
        }
        else {
            counter = 1;
        }
    }

    return max;
}

