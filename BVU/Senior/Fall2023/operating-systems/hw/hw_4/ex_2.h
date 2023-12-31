#include <pthread.h>
#include <unistd.h>

struct Matrix {
    int *mat;
    int rows;
    int cols;
} typedef Matrix;

struct ThreadArgs {
    Matrix *mat1;
    Matrix *mat2;
    int *dest;
    int start_pos;
} typedef ThreadArgs;

/* Get row from Matrix mat and store in integer array dest */
void Matrix_get_row(Matrix mat, int row, int *dest) {
    int row_shift = row * mat.cols;
    for (int i=0; i<mat.cols; i++) {
        dest[i] = mat.mat[i+row_shift]; 
    }
}

/* Get column from Matrix mat and store in integer array dest */
void Matrix_get_column(Matrix mat, int col, int *dest) {
    for (int i=0; i<mat.rows; i++) {
        dest[i] = mat.mat[(i*mat.cols) + col]; 
    }
}

/* Multiply a row and column vector and return the result */
int Matrix_mult_row_col(int *row, int *col, int n) {
    int sum = 0; 
    for (int i=0; i<n; i++) 
        sum += (row[i] * col[i]);

    return sum;
}

void* threadFunc(void* arg) {
    /* Create ThreadArgs pointer */
    ThreadArgs *args = (ThreadArgs*) arg;

    /* Create row and col array for current column */
    int row[args->mat1->cols];
    int col[args->mat2->rows];

    /* Initialize variables to */
    int i, j;
    int size = (args->mat1->rows * args->mat2->cols);
    
    /* Calculate one positon of destination array then go 4 postions 
     * forward since there is 4 threads. */
    for (int idx = args->start_pos; idx < size; idx += 4) {
        i = idx/(args->mat2->cols); // get row number
        j = idx%(args->mat2->cols); // get col number
        Matrix_get_row(*(args->mat1), i, row);
        Matrix_get_column(*(args->mat2), j, col);
        args->dest[idx] = Matrix_mult_row_col(row, col, args->mat1->cols);
    }
}

void m_mult_threaded(int *mat1, int mat1_m, int mat1_n,
        int *mat2, int mat2_m, int mat2_n,
        int *mat3)
{
    /* Initialize Matrix structs */
    Matrix m1 = {mat1, mat1_m, mat1_n};
    Matrix m2 = {mat2, mat2_m, mat2_n};

    /* Initialize ThreadArgs structs (pass m1 and m2 by reference) */
    ThreadArgs args0 = {&m1, &m2, mat3, 0};
    ThreadArgs args1 = {&m1, &m2, mat3, 1};
    ThreadArgs args2 = {&m1, &m2, mat3, 2};
    ThreadArgs args3 = {&m1, &m2, mat3, 3};

    /* Create an array of ThreadArgs for easy use */
    ThreadArgs args[] = {args0, args1, args2, args3};

    /* Create pthreads */
    int num_threads = 4;
    pthread_t thread[num_threads];

    /* Set threads loose */
    for (int i=0; i < 4; i++) {
        pthread_create(&(thread[i]),  // thread ID
                       0,             // default attributes
                       threadFunc,    // start routine
                       &args[i]);     // argument
    }
   
    for (int i = 0; i < num_threads; i++)
        pthread_join(thread[i], NULL);
    
    return;
}
