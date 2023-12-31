#include <stdio.h>
#include <stdlib.h>
#include "ex_2.h"

int main(int argc, char** argv) {

    char* str = instr("Held!", "lo Worl", 3);
    printf("%s\n", str);

    free(str);
    return 0;
}
