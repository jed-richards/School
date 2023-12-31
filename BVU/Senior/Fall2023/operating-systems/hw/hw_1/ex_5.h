#ifndef EX5_H
#define EX5_H

#include <stdio.h>
#include "linkedList.h"

void list_clear(struct Node** headPtr) {
    Node* head = *headPtr;
    Node* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    // set head to point to NULL (seg fault if this isn't done)
    *headPtr = NULL;

    return;
}

#endif /* EX5_H */
