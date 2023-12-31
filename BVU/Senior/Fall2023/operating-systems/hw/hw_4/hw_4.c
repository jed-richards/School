#include <stdio.h> 
#include "ex_1.h"
#include "ex_2.h"
#include "ex_3.h"

void test_matrix_mult(
        int *mat1, int mat1_m, int mat1_n,
        int *mat2, int mat2_m, int mat2_n,
        int *ans, int threadFlag)
{
    int size = mat1_m * mat2_n;
    int res[size];

    if (threadFlag)
        m_mult_threaded(mat1, mat1_m, mat1_n, mat2, mat2_m, mat2_n, res);
    else
        m_mult(mat1, mat1_m, mat1_n, mat2, mat2_m, mat2_n, res);

    int i, correct = 1;
    for(i=0; i < size; ++i) {
        if (res[i] != ans[i])
            correct = 0;
    }
    
    if (correct)
        printf("Matrix Multiplication Succeeded\n");
    else
        printf("Matrix Multiplication Failed\n");
}


void run_matrix_test(int threadFlag) {
    int m1[] = {2,3,4,5};
    int m2[] = {1,3,2,2};
    int m3[] = {8,12,14,22};
    test_matrix_mult(m1, 2, 2, m2, 2, 2, m3, threadFlag);


    int m4[] = {1,2,3,3,2,1};
    int m5[] = {4,5,6,6,5,4,4,6,5};
    int m6[] = {28,33,29,28,31,31};
    test_matrix_mult(m4, 2, 3, m5, 3, 3, m6, threadFlag);

    int m7[] = {1,2,3,3,2,1,2,1,3,2,3,1};
    int m8[] = {4,5,6,12,2,3,6,5,4,1,22,3,4,6,5,1,2,32};
    int m9[] = {28,33,29,17,52,105,28,31,31,39,52,47,26,33,31,28,32,105,30,31,29,28,72,47};
    test_matrix_mult(m7, 4, 3, m8, 3, 6, m9, threadFlag);
}

int main(int argc, char** argv) {
    int M,N;

    // Test ex1
    printf("Running tests for ex_1\n");
    int NOT_THREADED = 0;
    run_matrix_test(NOT_THREADED);

    // Test ex2
    printf("\nRunning tests for ex_2\n");
    int THREADED = 1;
    run_matrix_test(THREADED);

    // Run ex3
    printf("\nStarting Dining Philosophers\n");
    //float res = dine_philosophers_dine(5, 5);
    float res = dine_philosophers_dine(6, 6);
    //float res = dine_philosophers_dine(100, 100);
    printf("Attempts to eating ratio: %.2f\n", res);

    return 0;
}
