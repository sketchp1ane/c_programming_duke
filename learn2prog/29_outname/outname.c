#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {

    char * outName = malloc(strlen(inputName) * sizeof(*outName) + 8);
    strcpy(outName, inputName);
    strcat(outName, ".counts");
    return outName;
}
