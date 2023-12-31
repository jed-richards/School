#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *next;
    int data;
} typedef Node;

void list_print(struct Node *head) {
    struct Node *curr;
    printf("{");
    for(curr=head; curr != NULL; curr=curr->next) {
        printf("%d", curr->data);
        if (curr->next != NULL)
            printf(", ");
    }
    printf("}\n");
}

#endif /* LINKEDLIST_H */
