#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

int main() {

    // Initialize array
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }

    #pragma omp parallel for // the execution of 10 loops is distributed on the threads
    for (int i = 0; i < 10; i++) {
        printf("Thread %d processed element %d\n", omp_get_thread_num(), array[i]);
    }

    
    int i;
    #pragma omp parallel for lastprivate(i)
    for(i = 0; i < 9; i++) {
        // some code
    }
    printf("I = %d\n", i); // 9 (took the last value from the last iteration)
    printf("\n\n");

    return 0;
}
