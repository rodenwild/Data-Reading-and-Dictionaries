//
// Created by roden on 8/12/2022.
//

#ifndef COMP20003_A1_LINKEDLIST_H
#define COMP20003_A1_LINKEDLIST_H

typedef struct node node_t;
struct node {
    void *data;
    node_t *next;
};

typedef struct {
    node_t *head;
    node_t *foot;
} linkedlist_t;

/**
 * Creates an empty linked list
 * @return Newly created linked list
 * */
linkedlist_t *createLinkedlist();

/**
 * Inserts an item to the foot/end of the linked list
 * @param ll Linked list for item to be inserted into
 * @param data Pointer to data to be inserted
 * @return The linked list
 * */
linkedlist_t *insertFoot(linkedlist_t *ll, void *data);

/**
 * Frees memory used by linked list
 * @param ll Linked list to be freed
 * @param freeData Function pointer to free memory in linked list node data
 * @return void
 * */
void freeList(linkedlist_t *ll, void (*freeData)(void *data));

#endif //COMP20003_A1_LINKEDLIST_H
