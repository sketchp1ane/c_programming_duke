#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
    counts_t * counts = malloc(sizeof (counts_t));
    if (counts == NULL) {
        perror("Failed to allocate memory for counts\n");
        return NULL;
    }
    counts->array = malloc(sizeof (one_count_t));
    counts->length = 0;
    return counts;

}

int findCount(counts_t * c, const char * name) {

    for (int i = 0; i < c->length; i++) {
        if (strcmp(name, c->array[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void addCount(counts_t * c, const char * name) {
    if (name == NULL) {
        name = "<unknown> ";
    }
    int name_index = findCount(c, name);
    int temp = c->length;
    if (temp == 0 || name_index == -1) {

        c->array[temp].name = malloc((strlen(name) + 1) * sizeof (char));
        if (c->array[temp].name == NULL) {
            perror("Failed to allocate memory for name\n");
        }



        strcpy(c->array[temp].name, name);


        c->array[temp].num_of_times = 1;

        //for next count
        c->length++;
        temp = c->length;
        c->array = realloc(c->array, (temp + 1) * sizeof (one_count_t));
        if (c->array == NULL) {
            perror("Failed to allocate memory for next count\n");
        }
        c->array[temp].name = NULL;

    } else {
        c->array[name_index].num_of_times++;
    }

}
void printCounts(counts_t * c, FILE * outFile) {
    if (outFile == NULL) {
        perror("Please give a correct input stream\n");
        return;
    }
    int nullIsExist = 0;
    int nullIndex = -1;
    for (int i = 0; i < c->length; i++) {
        if (strcmp(c->array[i].name, "<unknown> ") == 0) {
            nullIsExist = 1;
            nullIndex = i;
            continue;
        }
        fprintf(outFile, "%s: %d\n", c->array[i].name,  c->array[i].num_of_times);
    }
    if (nullIsExist) {
        fprintf(outFile, "%s: %d\n", c->array[nullIndex].name,  c->array[nullIndex].num_of_times);
    }
}

void freeCounts(counts_t * c) {
    for (int i = 0; i < c->length; i++) {
        free(c->array[i].name);
    }
    free(c->array);
    free(c);
}
