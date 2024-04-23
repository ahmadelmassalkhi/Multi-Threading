#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h> // for sleep()

/**
 * @brief Illustrates how to 
 * use private & shared clauses
 **/
int main(int argc, char *argv[]) {
    int A = 5;
    int B = 5;
    
    #pragma omp parallel private(A, B) // every thread will have their own copies of A & B
    {
        // A & B will be considered un-assigned at start
        printf("A = %d\n", A); // garbage values
        printf("B = %d\n", B); // garbage values
        A = B = 10;
    }
    printf("A = B = %d\n", A); // 5 (not changed to 10 because private)
    printf("\n\n");


    #pragma omp parallel firstprivate(A, B) // like private
    {
        // BUT initial values of A & B are used
        printf("A = %d\n", A); // 5
        printf("B = %d\n", B); // 5
        A = B = 10;
    }
    printf("A = B = %d\n", A); // 5 (not changed to 10 because firstprivate makes them private)
    printf("\n\n");

    int sum = 0;
    #pragma omp parallel shared(sum) // the same variable `sum` will be shared accross all threads
    {
        #pragma omp critical // synchronized (block of code)
        {
            sum++;
        }
        
        #pragma omp atomic // synchronized (one line)
        sum++;
    }
    printf("Sum = %d\n", sum); // sum changed because it was shared
	
    return 0;
}
