//
// Created by roden on 8/11/2022.
//

#ifndef COMP20003_A1_DATA_H

#include <stdio.h>
#include "linkedList.h"

#define COMP20003_A1_DATA_H
#define MAX_LINE_LEN 512
#define MAX_VALUE_LEN 128
#define MATCH 1
#define NO_MATCH 0
#define NUMBER_OF_FIELDS 19

struct footpath {
    int footpath_id;                // - The row number for this footpath in the original full dataset. (integer)
    char *address;                  // - A name describing the location of the footpath. (string)
    char *clue_sa;                  // - The CLUE small area the footpath is in. (string)
    char *asset_type;               // - The name of the type of footpath. (string)
    double deltaz;                  // - The change in vertical distance along the footpath. (double)
    double distance;                // - The length of the footpath (full geometry) in metres. (double)
    double grade1in;                // - The percentage gradient of the footpath (full geometry). (double)
    int mcc_id;                     // - The id number identifying the footpath. (integer)
    int mccid_int;                  // - A second number identifying the road or intersection the footpath borders. (integer)
    double rlmax;                   // - The highest elevation on the footpath. (double)
    double rlmin;                   // - The lowest elevation on the footpath. (double)
    char *segside;                  // - The side of the road which the footpath is on. (string)
    int statusid;                   // - The status of the footpath. (integer)
    int streetid;                   // - The ID of the first street in the Address. (integer)
    int street_group;               // - The footpath_id of one of the footpaths connected to this footpath without a gap. (integer)
    double start_lat;               // - The latitude (y) of the starting point representing the line approximation of the footpath. (double)
    double start_lon;               // - The longitude (x) of the starting point representing the line approximation of the footpath. (double)
    double end_lat;                 // - The latitude (y) of the ending point representing the line approximation of the footpath. (double)
    double end_lon;                 // - The longitude (x) of the starting point representing the line approximation of the footpath. (double)
};

typedef struct footpath footpath_t;

/**
 * Reads a footpath record from a csv line
 * @param f Pointer to FILE of csv
 * @return Footpath struct pointer with csv data inside
 * */
footpath_t *readFootpathRecord(FILE *f);

/**
 * Traverses a line of a CSV file and returns the string
 * @param s CSV string
 * @param i Starting index for search
 * @return String CSV value
 * */
char *traverseLine(const char *s, int *i);

/**
 * Constructs footpath struct from an array of CSV values
 * @param array CSV values
 * @return Pointer to footpath struct with values filled in
 * */
footpath_t *createFootpathFromArray(char *array[]);

/**
 * Finds matches based off address
 * @param target Search string
 * @param ll Linked list to search
 * @param outFile File to output results to
 * @return void
 * */
void findMatches(char *target, linkedlist_t *ll, FILE *outFile);

/**
 * Checks if two strings match
 * @param sA First string to compare
 * @param sB Second string to compare
 * @return MATCH or NO_MATCH
 * */
int matchString(const char *sA, const char *sB);

/**
 * Outputs the matching footpath data
 * @param outFile File to output results to
 * @param match Footpath to output
 * @return void
 * */
void processMatches(FILE *outFile, footpath_t *match);

/**
 * Frees memory used by footpath
 * @param data footpath struct to be freed
 * @return void
 * */
void freeFootpath(void *data);

#endif //COMP20003_A1_DATA_H
