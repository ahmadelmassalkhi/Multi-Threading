#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define rows_A 100 // number of rows in matrix A
#define cols_A 100 // number of columns in matrix A
#define cols_B 100 // number of columns in matrix B


/* Initialize matrix a with random values */
void init_RandomMatrix_Parallel(int **A, int rows, int cols) {
    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A[i][j] = rand() % 10; // Random value between 0 and 9
        }
    }
}

void print_Matrix_Parallel(int **A, int rows, int cols) {
    #pragma omp parallel for ordered
    for (int i = 0; i < rows; i++) {
        #pragma omp ordered
        {
            for (int j = 0; j < cols; j++) printf("%d ", A[i][j]);
            printf("\n");
        }
    } // not ideal for printing the matrix. 
      // It serializes the printing operation, which defeats the purpose of parallelism
}

int** define_Matrix_Parallel(int rows, int cols) {
    int **matrix = (int **) malloc(sizeof(int *) * rows);
    #pragma omp parallel for
    for(int i = 0; i < rows; i++) matrix[i] = (int *) malloc(sizeof(int) * cols);
    return matrix;
}

int main() {
    int start = omp_get_wtime();

    /* Define empty matrices a, b, c */
    int **a = define_Matrix_Parallel(rows_A, cols_A);
    int **b = define_Matrix_Parallel(cols_A, cols_B);
    int **c = define_Matrix_Parallel(rows_A, cols_B);

    /* Initialize matrices a & b with random values */
    init_RandomMatrix_Parallel(a, rows_A, cols_A);
    init_RandomMatrix_Parallel(b, cols_A, cols_B);

    /* Perform matrix multiplication */
    #pragma omp parallel for
    for (int i = 0; i < rows_A; i++) {
        for (int j = 0; j < cols_B; j++) {
            int sum = 0;
            for (int k = 0; k < cols_A; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }

    /* Display the matrices and the result */
    printf("\nMatrix A:\n");
    print_Matrix_Parallel(a, rows_A, cols_A);

    printf("\nMatrix B:\n");
    print_Matrix_Parallel(b, cols_A, cols_B);

    printf("\nMatrix C = A x B:\n");
    print_Matrix_Parallel(c, rows_A, cols_B);


    printf("Time taken = %lf\n", omp_get_wtime() - start);
    return 0;
}
