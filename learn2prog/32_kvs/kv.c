#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


void stripNewline(char * str) {
    char *newline = strchr(str, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }
}


kvarray_t * readKVs(const char * fname) {
    char * currLine = NULL;
    size_t sz = 0;
    FILE * file = fopen(fname, "r");
    if (file == NULL) {
        perror("Failed to open file\n");
        return NULL;
    }
    kvarray_t *kvArray = malloc(sizeof(kvarray_t));
    if (kvArray == NULL) {
        perror("Failed to allocate memory to kvArray\n");
        fclose(file);
        return NULL;
    }
    kvArray->array = malloc(sizeof (kvpair_t));
    if (kvArray->array == NULL) {
        perror("Failed to allocate memory to a pair in array\n");
        fclose(file);
        return NULL;
    }
    kvArray->length = 0;
    kvpair_t *pair = &kvArray->array[0];

    while (getline(&currLine, &sz, file) >= 0) {

        //printf("The current line is %s", currLine);
        char * e_pos = strchr(currLine, '=');
        if (e_pos == NULL) {
            fprintf(stderr, "Please check the input line : %s\n", currLine);
            return NULL;
        }
        size_t key_len = e_pos - currLine ;
        size_t value_len = strlen(currLine) - key_len - 1;
        pair->key = malloc((key_len + 1)* sizeof(char));
        if (pair->key == NULL) {
            perror("Failed to allocate memory to key\n");
            return NULL;
        }
        pair->value = malloc((value_len + 1)* sizeof(char));
        if (pair->value == NULL) {
            perror("Failed to allocate memory to value\n");
            return NULL;
        }
        strncpy(pair->key, currLine, key_len);
        pair->key[key_len] = '\0';
        strcpy(pair->value, e_pos + 1);
        pair->value[value_len] = '\0';
        stripNewline(pair->value);





        kvArray->length++;
        int temp = kvArray->length;
        kvArray->array = realloc(kvArray->array, (temp + 1) * sizeof (kvpair_t));
        pair = &kvArray->array[temp];





    }
    free(currLine);
    fclose(file);
    return kvArray;
}

void freeKVs(kvarray_t * pairs) {
    for (int i = 0; i < pairs->length; i++) {
        free(pairs->array[i].key);
        free(pairs->array[i].value);
    }
    free(pairs->array);
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
    for (int i = 0; i < pairs->length; i++) {
        printf("key = '%s' value = '%s'\n", pairs->array[i].key, pairs->array[i].value);
    }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
    for (int i = 0; i < pairs->length; i++) {
        if (strcmp(pairs->array[i].key, key) == 0) {
            return pairs->array[i].value;
        }
    }
    return NULL;
}
