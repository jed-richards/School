#ifndef EX3_H
#define EX3_H

#include <stdio.h>

int* merge(int* arr1, int arr1Length, int* arr2, int arr2Length) {
    int* outarr = malloc( (arr1Length+arr2Length) * sizeof(int) );
    
    int i, ptr1, ptr2;
    ptr1 = ptr2 = 0;

    // populate outarr
    for (i=0; i != (arr1Length + arr2Length); i++) {
        if (ptr1 == arr1Length) {
            outarr[i] = arr2[ptr2];
            ptr2++;
        } 
        else if (ptr2 == arr2Length) {
            outarr[i] = arr1[ptr1];
            ptr1++;
        }
        else if (arr1[ptr1] <= arr2[ptr2]) {
            outarr[i] = arr1[ptr1];
            ptr1++;
        }
        else if (arr1[ptr1] > arr2[ptr2]) {
            outarr[i] = arr2[ptr2];
            ptr2++;
        }
    }

    return outarr;
}

#endif /* EX3_H */
