#ifndef EX1_H
#define EX1_H

#include <stdio.h>
#include <stdlib.h>

void printTriangle(int baseLength) {
    int height = (baseLength/2) + 1;  // ceiling
    int n = (baseLength/2) + 1; // initial spaces
    char* spaces = (char*) malloc(n * sizeof(char));
    char* head = spaces; // keep reference to beginning
    char ch = '#';

    // Initialize char array
    for (int i=0; i < n-1; i++) 
        spaces[i] = ' ';
    spaces[n-1] = '\0'; // append null byte

    int numChars; 
    for (int i=0; i < height; i++) {
        numChars = (2*i) + 1;
        printf("%s", spaces);
        for (int j=0; j < numChars; j++)
            printf("%c", ch);
        printf("%s\n", spaces);
        spaces++; // advance pointer (decrease number of spaces by one)
    }
    free(head); // free malloc
}

#endif /* EX1_H */
