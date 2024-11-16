#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

char ** readFilesToLines(FILE *file, size_t *lineCount) {
    char **lines = NULL;
    char *currLine = NULL;
    size_t sz = 0;
    *lineCount = 0;

    while (getline(&currLine, &sz, file) >= 0) {
        lines = realloc(lines, (*lineCount + 1) * sizeof(char *));
        if (lines == NULL) {
            perror("Memory allocation failed");
            free(currLine);
            return NULL;
        }
        lines[*lineCount] = currLine;
        currLine = NULL;
        (*lineCount)++;
    }

    free(currLine);
    return lines;
}

void sortAndPrint(char ** lines, int lineCount) {
    sortData(lines, lineCount);
    for (int i = 0; i < lineCount; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char ** argv) {
    if (argc < 1) {
        perror("Please input the correct arguments");
        return EXIT_FAILURE;
    }


    char **lines = NULL;
    size_t lineCount = 0;

    if (argc == 1) {
        lines = readFilesToLines(stdin, &lineCount);
        if (lines == NULL) {
            perror("Failed to read lines from stdin");
            return EXIT_FAILURE;
        }
        sortAndPrint(lines, lineCount);
    } else {
       for (int i = 1; i < argc; i++) {
           FILE *file = fopen(argv[i], "r");
           if (file == NULL) {
               perror("Failed to open file");
               return EXIT_FAILURE;
           }
           lines = readFilesToLines(file, &lineCount);
           if (lines == NULL) {
               perror("Failed to read lines from files");
               return EXIT_FAILURE;
           }
           fclose(file);
           sortAndPrint(lines, lineCount);
           lineCount = 0;
       }

    }

    return EXIT_SUCCESS;





}
