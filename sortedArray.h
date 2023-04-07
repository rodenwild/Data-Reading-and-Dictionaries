//
// Created by roden on 8/14/2022.
//

#ifndef COMP20003_A1_SORTEDARRAY_H
#define COMP20003_A1_SORTEDARRAY_H

#define INITIAL_ARRAY_SIZE 1
#define SUCCESS 1
#define FAIL 0

typedef struct {
    void **A;
    int size;
    int n;
} sortedArray_t;

/**
 * Creates an empty array
 * @return Newly created array
 * */
sortedArray_t *arrayCreate();

/**
 * Inserts an item into the sorted array
 * @param data Array to insert data
 * @param value pointer to data to be inserted
 * @return SUCCESS or FAIL
 * */
int insert(sortedArray_t *data, void *value);

/**
 * Prepares an array for an item insertion,
 * If there is no room in the array, the size is doubled
 * @param data Array to prepare
 * @return SUCCESS or FAIL
 * */
int prepareInsert(sortedArray_t *data);

/**
 * Uses a binary search algorithm to find the index of the closest value
 * @param data Array to search
 * @param grade1in grade1in value to match
 * @return Closest value index
 * */
int binarySearchClosest(sortedArray_t *data, double grade1in);

/**
 * Outputs the information of the match
 * @param data Array with match
 * @param grade1in grade1in value to match
 * @param outFile File to output information
 * @return void
 * */
void processClosest(sortedArray_t *data, char *grade1in, FILE *outFile);

/**
 * Frees the data used by an array
 * @param array Array to free
 * @param freeData Function pointer used to free data of array value
 * @return void
 * */
void freeArray(sortedArray_t *array, void (*freeData)(void *data));

#endif //COMP20003_A1_SORTEDARRAY_H
