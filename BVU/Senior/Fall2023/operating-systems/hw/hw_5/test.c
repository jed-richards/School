#include <assert.h>
#include <stdio.h>
#include "bvMemory.h"

void print_data_list() {
    struct DataNode* curr;
    printf("{\n");
    for(curr=data_head; curr != NULL; curr=curr->next) {
        if (curr->next != NULL) {
            printf("[ Next:  %p ]\n", curr->next->start);
        }
        else {
            printf("[ Next:  %p ]\n", curr->next);
        }
        printf("[ Start: %p | End: %p ]\n", curr->start, curr->end);
        printf("[ Size:  %ld ]\n\n", (curr->end - curr->start));
    }
    printf("}\n");
}

void print_slab_info() {
    printf("[Slab Address: %p to %p]\n", slab, slab+1000);
    printf("[Slab Size: %ld]\n", ((slab+1000) - slab));
}

void test_free_one_item() {
    char* arr1 = bvMalloc(100*sizeof(char), 0);
    bvFree(arr1);
    assert(data_head == NULL);
}

void test_free_beginning() {
    char* arr1 = bvMalloc(100*sizeof(char), 0);
    char* arr2 = bvMalloc(100*sizeof(char), 0);
    bvFree(arr1);
    assert( (char *) data_head->start == arr2);
    bvFree(arr2);
}

void test_free_middle() {
    char* arr1 = bvMalloc(100*sizeof(char), 0);
    char* arr2 = bvMalloc(100*sizeof(char), 0);
    char* arr3 = bvMalloc(100*sizeof(char), 0);
    bvFree(arr2);
    assert( (char *) data_head->next->start == arr3);
    bvFree(arr1);
    bvFree(arr3);
}

void test_free_full() {
    char* arr1 = bvMalloc(100*sizeof(char), 0);
    char* arr2 = bvMalloc(100*sizeof(char), 0);
    char* arr3 = bvMalloc(100*sizeof(char), 0);
    char* arr4 = bvMalloc(100*sizeof(char), 0);
    char* arr5 = bvMalloc(100*sizeof(char), 0);
    char* arr6 = bvMalloc(100*sizeof(char), 0);
    char* arr7 = bvMalloc(100*sizeof(char), 0);
    char* arr8 = bvMalloc(100*sizeof(char), 0);
    char* arr9 = bvMalloc(100*sizeof(char), 0);
    char* arr10 = bvMalloc(100*sizeof(char), 0);
    bvFree(arr10);
    bvFree(arr1);
    bvFree(arr9);
    bvFree(arr2);
    bvFree(arr8);
    bvFree(arr3);
    bvFree(arr7);
    bvFree(arr4);
    bvFree(arr6);
    bvFree(arr5);
    assert(data_head == NULL);
}

void test_best_fit() {
    char* arr1 = bvMalloc(100*sizeof(char), 0);
    char* arr2 = bvMalloc(850*sizeof(char), 0);
    bvFree(arr1);
    char* arr3 = bvMalloc(50*sizeof(char), 1);
    assert( (char *) data_head->next->start == arr3);
    bvFree(arr2);
    bvFree(arr3);
}

void test_first_fit() {
    char* arr1 = bvMalloc(100*sizeof(char), 0);
    char* arr2 = bvMalloc(850*sizeof(char), 0);
    bvFree(arr1);
    char* arr3 = bvMalloc(50*sizeof(char), 0);
    assert( (char *) data_head->start == arr3);
    bvFree(arr2);
    bvFree(arr3);
}

void test_best_fit2() {
    char* arr1 = bvMalloc(100*sizeof(char), 0);
    char* arr2 = bvMalloc(50*sizeof(char), 0);
    char* arr3 = bvMalloc(350*sizeof(char), 0);
    char* arr4 = bvMalloc(25*sizeof(char), 0);
    char* arr5 = bvMalloc(475*sizeof(char), 0);

    bvFree(arr2);
    bvFree(arr4);

    char* arr6 = bvMalloc(25*sizeof(char), 1);
    assert( (char *) data_head->next->next->start == arr6);
    char* arr7 = bvMalloc(25*sizeof(char), 1);
    assert( (char *) data_head->next->start == arr7);

    bvFree(arr1);
    bvFree(arr3);
    bvFree(arr5);
    bvFree(arr6);
    bvFree(arr7);
}

void test_first_fit2() {
    char* arr1 = bvMalloc(100*sizeof(char), 0);
    char* arr2 = bvMalloc(50*sizeof(char), 0);
    char* arr3 = bvMalloc(350*sizeof(char), 0);
    char* arr4 = bvMalloc(25*sizeof(char), 0);
    char* arr5 = bvMalloc(475*sizeof(char), 0);

    bvFree(arr2);
    bvFree(arr4);

    char* arr6 = bvMalloc(25*sizeof(char), 0);
    assert( (char *) data_head->next->start == arr6);
    char* arr7 = bvMalloc(25*sizeof(char), 0);
    assert( (char *) data_head->next->next->start == arr7);

    bvFree(arr1);
    bvFree(arr3);
    bvFree(arr5);
    bvFree(arr6);
    bvFree(arr7);
}

void test_malloc_when_full() {
    char* arr1 = bvMalloc(1000*sizeof(char), 0);
    char* arr2 = bvMalloc(100*sizeof(char), 0);
    assert(arr2 == NULL);
    bvFree(arr1);
}

int main() {
    printf("test1\n");
    test_free_one_item();
    print_data_list();

    printf("test2\n");
    test_free_beginning();
    print_data_list();

    printf("test3\n");
    test_free_middle();
    print_data_list();

    printf("test4\n");
    test_free_full();
    print_data_list();

    printf("test5\n");
    test_best_fit();
    print_data_list();

    printf("test6\n");
    test_first_fit();
    print_data_list();

    printf("test7\n");
    test_best_fit2();
    print_data_list();

    printf("test8\n");
    test_first_fit2();
    print_data_list();

    printf("test9\n");
    test_malloc_when_full();
    print_data_list();
    return 0;
}
