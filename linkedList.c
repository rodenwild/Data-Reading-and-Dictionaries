//
// Created by roden on 8/12/2022.
//

#include <stdlib.h>
#include <assert.h>
#include "linkedList.h"

linkedlist_t *createLinkedlist()
{
    linkedlist_t *ll = (linkedlist_t *) malloc(sizeof(linkedlist_t));
    assert(ll);
    /* Initialise head and foot to NULL */
    ll->head = NULL;
    ll->foot = NULL;
    return ll;
}

linkedlist_t *insertFoot(linkedlist_t *ll, void *data)
{
    node_t *new_node;
    new_node = (node_t *) malloc(sizeof(*new_node));
    assert(ll);
    assert(new_node);
    new_node->data = data;
    new_node->next = NULL;
    /* If there is no head, then new node is also the head */
    if (ll->head == NULL)
    {
        ll->head = new_node;
    }
    /* If the foot is NULL, then simply make the new node the foot
     * If it is not NULL,
     * make old foot point to new node, and make new node the new foot*/
    if (ll->foot == NULL)
    {
        ll->foot = new_node;
    }
    else
    {
        ll->foot->next = new_node;
        ll->foot = new_node;
    }
    return ll;
}

void freeList(linkedlist_t *ll, void (*freeData)(void *data))
{
    node_t *node = ll->head;
    /* Traverse linked list */
    while (node)
    {
        /* Pointer to function used to free nodes data */
        (*freeData)(node->data);
        node_t *oldNode = node;
        node = node->next;
        free(oldNode);
    }
    free(ll);
}