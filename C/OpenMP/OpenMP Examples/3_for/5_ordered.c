#include <omp.h>
#include <stdio.h>

int main() {
    int i;

    #pragma omp parallel for ordered
    for(i = 0; i < 10; i++) {
        printf("Unordered Iteration %d by thread %d\n", i, omp_get_thread_num());

        // region that will be executed in order
        #pragma omp ordered // must be closely nested inside a loop region with an 'ordered' clause
        {
            printf("Iteration %d by thread %d\n", i, omp_get_thread_num());
        }

        /*
            You can't use a barrier region inside an ordered directive because 
            barriers can potentially disrupt the order of execution that the ordered clause is supposed to guarantee
        */
        // #pragma omp barrier
    }

    return 0;
}



