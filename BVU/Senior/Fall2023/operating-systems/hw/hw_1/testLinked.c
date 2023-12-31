#include <stdio.h>
#include "linkedList.h"
#include "ex_4.h"
#include "ex_5.h"

Node* test1() {
    Node* head = malloc(sizeof(Node));
    head->next = NULL;
    head->data = 12;
    list_insert(&head, 200);
    list_insert(&head, 2);
    list_insert(&head, 8);

    return head;
}

Node* test2() {
    Node* head = NULL;
    list_insert(&head, 1);

    return head;
}

Node* test3() {
    Node* head = NULL;
    list_insert(&head, 3);
    list_insert(&head, 1);
    list_insert(&head, 2);

    return head;
}

int main(int argc, char** argv) {
    //Node* head = test1();
    //Node* head = test2();
    Node* head = test3();
    
    printf("Before Clear:\n");
    list_print(head);

    list_clear(&head);

    printf("After Clear:\n");
    list_print(head);
    
    return 0;
}
