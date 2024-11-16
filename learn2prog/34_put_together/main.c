#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
    fprintf(stderr, "Starting countFile with filename: %s\n", filename);
    counts_t * counts = createCounts();
    assert(counts != NULL);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        freeCounts(counts);
        return NULL;
    }

    char *currLine = NULL;
    size_t sz = 0;
    while (getline(&currLine, &sz, file) != -1) {
        // Debug information for each line read
        fprintf(stderr, "Read line: %s\n", currLine);

        // Strip the newline character
        char *newline = strchr(currLine, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        char *value = lookupValue(kvPairs, currLine);
        if (value != NULL) {
            addCount(counts, value);
            fprintf(stderr, "Value found: %s\n", value);
        } else {
            addCount(counts, NULL);
            fprintf(stderr, "Warning: Key '%s' not found in kvPairs\n", currLine);
        }
    }
    fclose(file);
    free(currLine);
    fprintf(stderr, "Finished countFile for filename: %s\n", filename);
    return counts;
}

int main(int argc, char ** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: ./count_values kvs.txt list1a.txt list1b.txt...\n");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "Reading key/value pairs from file: %s\n", argv[1]);
    kvarray_t * kvPairs = readKVs(argv[1]);
    if (kvPairs == NULL) {
        fprintf(stderr, "Failed to read key/value pairs from %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    printKVs(kvPairs);

    for (int i = 2; i < argc; i++) {
        fprintf(stderr, "Processing file: %s\n", argv[i]);

        char *newFile = computeOutputFileName(argv[i]);
        if (newFile == NULL) {
            fprintf(stderr, "Failed to compute output file name for %s\n", argv[i]);
            freeKVs(kvPairs);
            return EXIT_FAILURE;
        }
        fprintf(stderr, "Output file name computed: %s\n", newFile);

        FILE *file = fopen(newFile, "w");
        if (file == NULL) {
            perror("Failed to open output file");
            free(newFile);
            freeKVs(kvPairs);
            return EXIT_FAILURE;
        }

        counts_t * counts = countFile(argv[i], kvPairs);
        if (counts == NULL) {
            fprintf(stderr, "Failed to count values in %s\n", argv[i]);
            fclose(file);
            free(newFile);
            freeKVs(kvPairs);
            return EXIT_FAILURE;
        }

        fprintf(stderr, "Printing counts for file: %s\n", argv[i]);
        printCounts(counts, stdout);
        printCounts(counts, file);

        fclose(file);
        free(newFile);
        freeCounts(counts);

        fprintf(stderr, "Completed processing for file: %s\n", argv[i]);
    }

    freeKVs(kvPairs);
    fprintf(stderr, "Completed all files. Exiting program.\n");

    return EXIT_SUCCESS;
}
