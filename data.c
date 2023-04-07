//
// Created by roden on 8/11/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "linkedList.h"
#include "data.h"

footpath_t *readFootpathRecord(FILE *f)
{
    char *footpathValues[NUMBER_OF_FIELDS] = {NULL};

    char line[MAX_LINE_LEN];
    /* Read a line in from file */
    if (fgets(line, MAX_LINE_LEN, f) == NULL)
    {
        return NULL;
    }
    char *tmp = strdup(line);
    int index = 0;
    /* Process each value in the CSV line and store in array */
    for (int i = 0; i < NUMBER_OF_FIELDS; i++)
    {
        footpathValues[i] = traverseLine(tmp, &index);
    }
    free(tmp);
    footpath_t *fp;
    /* Convert array of strings to footpath */
    fp = createFootpathFromArray(footpathValues);
    return fp;
}

char *traverseLine(const char *s, int *i)
{
    int openQuote = 0;
    int start = *i;
    char *temp = malloc(MAX_LINE_LEN * sizeof(char));
    assert(temp);
    int tracking = *i;
    /* Continue traversing csv row while not reaching the end,
     * or reach a comma and there isn't an opening quote without a closing one
     * */
    while ((openQuote == 1 || s[*i] != ',') && s[*i] != '\n' && s[*i] != EOF)
    {
        if (s[*i] == '"' && openQuote == 0)
        {
            openQuote = 1;
        } else if (s[*i] == '"' && openQuote == 1)
        {
            openQuote = 0;
        } else
        {
            temp[tracking - start] = s[*i];
            tracking++;
        }
        ++*i;
    }
    temp[tracking - start] = '\0';
    ++*i;
    return temp;
}

footpath_t *createFootpathFromArray(char *array[])
{
    footpath_t *fp = (footpath_t *) malloc(sizeof(footpath_t));

    assert(fp);
    /* Set all fields, converting to the correct data type
     * Then freeing the string afterwards */
    fp->footpath_id = atoi(array[0]);
    free(array[0]);
    fp->deltaz = atof(array[4]);
    free(array[4]);
    fp->distance = atof(array[5]);
    free(array[5]);
    fp->grade1in = atof(array[6]);
    free(array[6]);
    fp->mcc_id = atoi(array[7]);
    free(array[7]);
    fp->mccid_int = atoi(array[8]);
    free(array[8]);
    fp->rlmax = atof(array[9]);
    free(array[9]);
    fp->rlmin = atof(array[10]);
    free(array[10]);
    fp->statusid = atoi(array[12]);
    free(array[12]);
    fp->streetid = atoi(array[13]);
    free(array[13]);
    fp->street_group = atoi(array[14]);
    free(array[14]);
    fp->start_lat = atof(array[15]);
    free(array[15]);
    fp->start_lon = atof(array[16]);
    free(array[16]);
    fp->end_lat = atof(array[17]);
    free(array[17]);
    fp->end_lon = atof(array[18]);
    free(array[18]);

    /* For all string fields, space is malloced and then copied */
    fp->address = malloc(sizeof(char) * (strlen(array[1]) + 1));
    assert(fp->address);
    strcpy(fp->address, array[1]);
    free(array[1]);

    fp->clue_sa = malloc(sizeof(char) * (strlen(array[2]) + 1));
    assert(fp->clue_sa);
    strcpy(fp->clue_sa, array[2]);
    free(array[2]);

    fp->asset_type = malloc(sizeof(char) * (strlen(array[3]) + 1));
    assert(fp->asset_type);
    strcpy(fp->asset_type, array[3]);
    free(array[3]);

    fp->segside = malloc(sizeof(char) * (strlen(array[11]) + 1));
    assert(fp->segside);
    strcpy(fp->segside, array[11]);
    free(array[11]);

    return fp;
}

void findMatches(char *target, linkedlist_t *ll, FILE *outFile)
{
    int matchCount = 0;
    fprintf(outFile, "%s\n", target);
    node_t *node = ll->head;
    /* Traverse linked list looking for matches */
    while (node)
    {
        if (matchString(target, ((footpath_t *) node->data)->address) == MATCH)
        {
            /* If a match is found, process it and increment the match count */
            matchCount++;
            processMatches(outFile, (footpath_t *) node->data);
        }
        node = node->next;
    }
    if (matchCount > 0)
    {
        printf("%s --> %d\n", target, matchCount);
    } else
    {
        printf("%s --> NOTFOUND\n", target);
    }
}

int matchString(const char *sA, const char *sB)
{
    assert(sA && sB);

    int result = MATCH;
    int i = 0;
    while (sA[i] != '\0' && sB[i] != '\0')
    {
        /* If the characters do not match at any point, return NO_MATCH early */
        if (sA[i] != sB[i])
        {
            result = NO_MATCH;
            break;
        }
        i++;
    }
    /* Check that both are null terminated at the same index */
    if (result == MATCH && sA[i] == sB[i])
    {
        return MATCH;
    } else
    {
        return NO_MATCH;
    }
}

void processMatches(FILE *outFile, footpath_t *match)
{
    fprintf(outFile, "--> footpath_id: %d || address: %s || "
                     "clue_sa: %s || asset_type: %s || deltaz: %.2lf || "
                     "distance: %.2lf || grade1in: %.1lf || mcc_id: %d || "
                     "mccid_int: %d || rlmax: %.2lf || rlmin: %.2lf || "
                     "segside: %s || statusid: %d || streetid: %d || "
                     "street_group: %d || start_lat: %.6lf || "
                     "start_lon: %.6lf || end_lat: %.6lf || "
                     "end_lon: %.6lf || \n", match->footpath_id, match->address,
            match->clue_sa, match->asset_type, match->deltaz, match->distance,
            match->grade1in, match->mcc_id, match->mccid_int, match->rlmax,
            match->rlmin, match->segside, match->statusid, match->streetid,
            match->street_group, match->start_lat, match->start_lon,
            match->end_lat, match->end_lon);
}

void freeFootpath(void *data)
{
    free(((footpath_t *) data)->address);
    free(((footpath_t *) data)->clue_sa);
    free(((footpath_t *) data)->asset_type);
    free(((footpath_t *) data)->segside);
    free(data);
}