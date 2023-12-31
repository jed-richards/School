#include <stdio.h>
#include <stdlib.h>
#include "ex_3.h"

void printArray(int* arr, int length) {
    int i;
    printf("{");
    for(i=0; i < length; i++) {
        printf("%d", arr[i]);
        if (i != length-1)
            printf(", ");
    }
    printf("}\n");
}

int main(int argc, char** argv) {
    int arr1[] = {1, 4, 7, 9};
    int arr2[] = {1, 2, 3, 8, 13};

    int* arr3 = merge(arr1, 4, arr2, 5);
    printArray(arr3, 9);

    free(arr3);
    return 0;
}
