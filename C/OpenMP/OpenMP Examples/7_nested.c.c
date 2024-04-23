
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
/**
 * @brief Illustrates how to use the for construct.
 * @details This application contains a for loop that initialises an array. This
 * for loop is parallelised by using a for construct inside a parallel region.
 **/
int main(int argc, char* argv[])
{
    // set number of threads
    omp_set_num_threads(4);
 
    int a[10];
    #pragma omp parallel
    {
        // the inner parallel region will be executed serially by one of the threads from the outer parallel region
        // AND will execute the for loop N times (N = number of threads)
        #pragma omp parallel for
        for(int i = 0; i < 10; i++)
        {
            a[i] = i;
            printf(" I am thread %d, I filled a[%d] \n", omp_get_thread_num(), i);
        }
    }

    // enable nested parallelism
	omp_set_nested(1);

    #pragma omp parallel
    {
        // threads will share these iterations rather than running the entire iteration set each
        // AND will execute the for loop N times (N = number of threads)
        #pragma omp parallel for
        for(int i = 0; i < 10; i++)
        {
            a[i] = i;
			printf(" I am thread %d, I filled a[%d] \n", omp_get_thread_num(), i);
        }
    }
	
    return EXIT_SUCCESS;
}
