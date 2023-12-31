void get_row(int *mat, int mat_m, int mat_n, int row, int *dest) {
    // Fill row
    int row_shift = row * mat_n;
    for (int i=0; i<mat_n; i++) {
        dest[i] = mat[i+row_shift]; 
    }
}

void get_column(int *mat, int mat_m, int mat_n, int col, int *dest) {
    // Fill col
    for (int i=0; i<mat_m; i++) {
        dest[i] = mat[(i*mat_n) + col]; 
    }
}

int mult_row_col(int *row, int *col, int n) {
    int sum = 0; 
    for (int i=0; i<n; i++) 
        sum += (row[i] * col[i]);

    return sum;
}

void m_mult(int *mat1, int mat1_m, int mat1_n,
        int *mat2, int mat2_m, int mat2_n,
        int *mat3)
{
    int size = (mat1_m * mat2_n);
    int i, j;  // indices: (i = row, j = col)

    // initialize arrays:
    //   row: an array of size mat1_n (num columns) to hold mat1 rows
    //   col: an array of size mat2_m (num rows) to hold mat2 columns
    int row[mat1_n], col[mat2_m];

    for (int k=0; k<size; k++) {
        i = k/mat2_n;  // get row number
        j = k%mat2_n;  // get col number
        get_row(mat1, mat1_m, mat1_n, i, row);     // get row 'i' from mat1
        get_column(mat2, mat2_m, mat2_n, j, col);  // get col 'j' from mat2
        mat3[k] = mult_row_col(row, col, mat1_n);
    }

    return;
}
