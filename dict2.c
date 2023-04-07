//
// Created by roden on 8/14/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "data.h"
#include "sortedArray.h"

#define INPUT_FILE_INDEX 2
#define OUTPUT_FILE_INDEX 3

int main(int argc, char *argv[])
{
    sortedArray_t *data = arrayCreate();

    FILE *dataFile = fopen(argv[INPUT_FILE_INDEX], "r");
    FILE *outFile = fopen(argv[OUTPUT_FILE_INDEX], "w");
    assert(dataFile && outFile);
    /* Clear first line of data */
    while (fgetc(dataFile) != '\n');

    footpath_t *fp;
    /* Read all lines and insert into array */
    while ((fp = readFootpathRecord(dataFile)) != NULL
           && insert(data, fp) == SUCCESS);

    char *grade1in = (char *) malloc(MAX_VALUE_LEN * sizeof(char));
    /* Find closest matches for input */
    while (fgets (grade1in, MAX_VALUE_LEN, stdin))
    {
        grade1in[strlen(grade1in) - 1] = '\0';
        if (strlen(grade1in) == 0) break;
        processClosest(data, grade1in, outFile);
    }
    freeArray(data, freeFootpath);
    free(grade1in);
    fclose(dataFile);
    fclose(outFile);

    return 0;
}