#ifndef EX2_H
#define EX2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* instr(char* str1, char* str2, int n) {
    int size = strlen(str1) + strlen(str2);
    char* outstr = malloc(size * sizeof(char));
     
    strncat(outstr, str1, n);
    str1 += n; // advance pointer
    strcat(outstr, str2);
    strcat(outstr, str1);

    return outstr;
}

#endif /* EX2_H */
