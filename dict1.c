//
// Created by roden on 8/12/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "linkedList.h"

#define INPUT_FILE_INDEX 2
#define OUTPUT_FILE_INDEX 3

int main(int argc, char *argv[])
{
    linkedlist_t *ll = createLinkedlist();

    FILE *dataFile = fopen(argv[INPUT_FILE_INDEX], "r");
    FILE *outFile = fopen(argv[OUTPUT_FILE_INDEX], "w");
    assert(dataFile && outFile);
    /* Clear first line of data */
    while (fgetc(dataFile) != '\n');

    footpath_t *fp;
    /* Read all lines and insert into linked list */
    while ((fp = readFootpathRecord(dataFile)) != NULL)
    {
        ll = insertFoot(ll, fp);
    }

    char *target = malloc(MAX_VALUE_LEN * sizeof(char));
    assert(target);
    /* Read input and find matches */
    while (fscanf(stdin, "\n%[^\r\n]", target) == 1)
    {
        findMatches(target, ll, outFile);
    }
    free(target);
    freeList(ll, freeFootpath);
    fclose(dataFile);
    fclose(outFile);
    return 0;
}