#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
/**
 * @brief Illustrates the OpenMP default clause.
 **/
int main(int argc, char* argv[])
{
    // Use 2 OpenMP threads
    omp_set_num_threads(2);
 
    #pragma omp parallel default(shared)
    {
        // all variables defined outside this scope are shared
        // all variables defined inside this scope are private
    }

    // by default, default(shared) is set
    #pragma omp parallel
    {
        // same as default(shared)
    }

    // every variable must be EXPLICITLY declared as shared|private|threadprivate
    #pragma omp parallel default(none)
    {
    }

    /* EXAMPLE OF default(none) */
    int sum = 0;
    int n;
    #pragma omp parallel default(none) shared(sum) private(n)
    {
        n = omp_get_thread_num();
        sum += n;
    }
    printf("Sum = %d\n", sum);
    printf("N = %d\n", n);
    
    return EXIT_SUCCESS;
}
 
