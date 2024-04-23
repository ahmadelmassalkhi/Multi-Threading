#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


int main() {

    printf("\n\n");
    #pragma omp parallel
    {
        // This code block will be executed by multiple threads
        // ...
        
        #pragma omp single
        {
            // This code block will be executed by only one thread
            // All other threads will wait at this point until the execution of this block is complete
            printf("[Thread %d] Only a single thread executes this printf, I happen to be the one picked.\n", omp_get_thread_num());
        }

        #pragma omp single nowait
        {
            // This code block will be executed by only one thread
            // All other threads will NOT WAIT for this block to complete execution
            printf("HOOOOOOOOO HOOOOOOOOOOOOO\n");
        }

        // This code block will be executed by multiple threads
        // ...
    }
    printf("\n\n");


    return EXIT_SUCCESS;
}