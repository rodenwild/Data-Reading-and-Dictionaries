//
// Created by roden on 8/14/2022.
//

#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "sortedArray.h"

sortedArray_t *arrayCreate()
{
    sortedArray_t *data = malloc(sizeof(sortedArray_t));
    assert(data);
    /* Initial array has 1 position available which is empty */
    data->size = INITIAL_ARRAY_SIZE;
    data->A = malloc(sizeof(*(data->A)));
    assert(data->A);
    data->n = 0;
    return data;
}

int insert(sortedArray_t *data, void *value)
{
    /* First prepare for an insertion, and return FAIL if it fails to prepare */
    if (prepareInsert(data) == FAIL) return FAIL;
    double grade1in = ((footpath_t *) value)->grade1in;
    int i;
    for (i = data->n - 1; i >= 0; i--)
    {
        /* When the value to insert is no longer bigger than the array value,
         * Stop shifting the rest of the values */
        if (((footpath_t *) data->A[i])->grade1in <= grade1in) break;
        /* Otherwise shift the array value to the right */
        data->A[i + 1] = data->A[i];
    }
    data->A[i + 1] = value;
    data->n++;
    return SUCCESS;
}

int prepareInsert(sortedArray_t *data)
{
    /* If there is already enough room, return early */
    if (data->n < data->size) return SUCCESS;

    /* Double the size */
    data->size <<= 1;
    /* Reallocate the old array to a pointer with newly malloced memory */
    void *newData = realloc(data->A, data->size * sizeof(*(data->A)));
    /* If the realloc failed, half the size and return FAIL */
    if (newData == NULL)
    {
        data->size >>= 1;
        return FAIL;
    }
    data->A = newData;
    return SUCCESS;
}

int binarySearchClosest(sortedArray_t *data, double grade1in)
{
    footpath_t **array = (footpath_t **) data->A;
    /* If the new value is the smallest, return 0,
     * if biggest, return last index */
    if (grade1in <= array[0]->grade1in) return 0;
    if (grade1in >= array[data->n-1]->grade1in) return data->n-1;

    int low = 0, high = data->n, mid = 0;
    while (low < high)
    {
        mid = (low + high) / 2;
        if (array[mid]->grade1in == grade1in)       // Match
        {
            return mid;
        }
        if (grade1in < array[mid]->grade1in)        // Value to the left
        {
            /* If the new value is in the middle of two adjacent values */
            if (mid > 0 && grade1in > array[mid - 1]->grade1in)
            {   /* Return closest value */
                return ((grade1in - array[mid - 1]->grade1in)
                        <= (array[mid]->grade1in - grade1in))
                       ? mid - 1 : mid;
            }
            high = mid;
        }
        else                                        // Value to the right
        {
            if (mid < (data->n - 1) && grade1in < array[mid + 1]->grade1in)
            {   /* Return closest value */
                return ((grade1in - array[mid]->grade1in)
                        <= (array[mid + 1]->grade1in - grade1in))
                       ? mid : mid + 1;
            }
            low = mid + 1;
        }
    }
    return mid;
}

void processClosest(sortedArray_t *data, char *grade1in, FILE *outFile)
{
    fprintf(outFile, "%s\n", grade1in);
    double grade1in_val = atof(grade1in);
    int index = binarySearchClosest(data, grade1in_val);
    printf("%s --> %.1lf\n",grade1in, ((footpath_t *) data->A[index])->grade1in);
    /* Outputs a formatted footpath */
    processMatches(outFile, (footpath_t *) data->A[index]);
}

void freeArray(sortedArray_t *array, void (*freeData)(void *data))
{
    /* Use the function pointer to free all the array items */
    for (int i = 0; i < array->n; i++)
    {
        (*freeData)(array->A[i]);
    }
    free(array->A);
    free(array);
}