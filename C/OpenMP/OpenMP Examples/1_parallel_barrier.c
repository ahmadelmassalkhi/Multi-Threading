#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/**
 * @brief Illustrates how to 
 * create parallel region 
 * use barrier clause
 * use single clause
 **/
int main(int argc, char* argv[])
{
    // set number of threads (that will execute parallel regions)
    omp_set_num_threads(7); // if not set: 
                            // default number of threads = available hardware threads on the system
 
    // Create the parallel region
    #pragma omp parallel
    {
        // print thread id
        printf("[Thread %d]\n", omp_get_thread_num());
 
        // wait until all threads reach this line
        #pragma omp barrier

        printf("FINALLY\n");

    } /* main thread waits all threads to finish */
 
    printf("Resuming execution after all threads finished\n");
    return EXIT_SUCCESS;
}
