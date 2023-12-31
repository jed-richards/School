#ifndef EX4_H
#define EX4_H

#include <stdio.h>
#include "linkedList.h"

void list_insert(struct Node** headPtr, int value) {
    // create new node
    Node* n = (Node*) malloc(sizeof(Node));
    n->next = NULL;
    n->data = value;

    // check if empty
    if (*headPtr == NULL) {
        *headPtr = n;
    } 
    else if ( (*headPtr)->data > value ) {
        // insert at beggining
        n->next = *headPtr;
        *headPtr = n;
    } 
    else {
        Node* curr = *headPtr;

        // advance pointer until we find insert postion
        while (curr->next != NULL && curr->next->data <= value) {
            curr = curr->next;
        }

        // insert
        if (curr->next != NULL) {
            n->next = curr->next;
            curr->next = n;
        }
        else {
            curr->next = n;
        }
    }

    return;
}

#endif /* EX4_H */
