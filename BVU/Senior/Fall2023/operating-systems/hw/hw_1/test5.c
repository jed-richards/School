#include <stdio.h>
#include <stdlib.h>
#include "ex_5.h"

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
    return 0;
}
