#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
/**
 * @brief Illustrates the guided scheduling policy.
 * @details A for loop is parallelised across 2 threads using the guided
 * scheduling policy.
 **/
int main(int argc, char* argv[])
{
    // Use 2 threads when creating OpenMP parallel regions
    omp_set_num_threads(2);

    // Parallelise the for loop using the dynamic schedule
    printf("schedule(dynamic)\n");
    #pragma omp parallel for schedule(dynamic)
    for(int i = 0; i < 10; i++)
    {
        printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
    }
    printf("\n\n\n");
    
    // Parallelise the for loop using the dynamic schedule and chunks of 2 iterations
    printf("schedule(dynamic, 2)\n");
    #pragma omp parallel for schedule(dynamic, 2)
    for(int i = 0; i < 10; i++)
    {
        printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
    }
    printf("\n\n\n");
 
    // Parallelise the for loop using the guided schedule
    printf("schedule(guided)\n");
    #pragma omp parallel for schedule(guided)
    for(int i = 0; i < 10; i++)
    {
        printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
    }
    printf("\n\n\n");
 
    // Parallelise the for loop using the static schedule
    printf("schedule(static)\n");
    #pragma omp parallel for schedule(static)
    for(int i = 0; i < 10; i++)
    {
        printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
    }
    printf("\n\n\n");

    
    // Parallelise the for loop using the static schedule with chunks made of 2 iterations
    printf("schedule(static, 2)\n");
    #pragma omp parallel for schedule(static, 2)
    for(int i = 0; i < 10; i++)
    {
        printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
    }
    printf("\n\n\n");
    
    // Parallelise the for loop using the auto schedule
    printf("schedule(auto)\n");
    #pragma omp parallel for schedule(auto)
    for(int i = 0; i < 10; i++)
    {
        printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
    }

    return EXIT_SUCCESS;
}
