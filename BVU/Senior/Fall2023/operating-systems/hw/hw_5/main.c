#include <stdio.h>
#include "bvMemory.h"


int main() {

    int* slab = bvMalloc(1000*sizeof(int), 0);

    slab[0] = 1;

    printf("%d", slab[0]);

    return 0;
}
