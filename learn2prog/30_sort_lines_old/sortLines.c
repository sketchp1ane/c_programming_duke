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

int main(int argc, char ** argv) {
    if (argc == 0) {
        fprintf(stderr,"Usage: inputFileName\n");
        return EXIT_FAILURE;
    }

    char ** fileNames = malloc((argc - 1) * sizeof(char*));
    for (int i = 0; i < argc - 1; i++) {
        fileNames[i] = malloc((strlen(argv[i + 1]) + 1) * sizeof(char));
        strcpy(fileNames[i], argv[i + 1]);
    }


    for (int i = 0; i < argc - 1; i++) {
        FILE *file = fopen(fileNames[i], "r");
        if (file == NULL) {
            perror("Could not open file");
            return EXIT_FAILURE;
        }

        char *data = NULL;
        size_t sz = 0;
        while (getline(&data, &sz, file) >= 0) {
            sortData(&data, strlen(data));
            printf("%s", data);
        }

    }

    return EXIT_SUCCESS;

}
