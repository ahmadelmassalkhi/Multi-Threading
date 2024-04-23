#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main() {


    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < 100; i++) {
        } // contains implicit barrier (finished threads will wait until all threads are done)
    
        #pragma omp for nowait // removes the implicit barrier => no wait is needed
        for (int i = 0; i < 100; i++) {
        }
    }

    return EXIT_SUCCESS;
}