#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main(int argc, char *argv[])
{
    /* Some initializations */
    double a[N], b[N];
    for (int i = 0; i < N; i++)
        a[i] = b[i] = (double) i;

    double sum = 0;
    #pragma omp parallel for reduction(+ : sum) // sum is private by default (meaning every thread will have its own copy of `sum`)
    for (int i = 0; i < N; i++)
        sum = sum + (a[i] * b[i]);
    // at the end of the `#pragma omp parallel for`
    // reduction(+, sum) adds all `sum` local variables into the original `sum` variable

    printf("Sum = %f\n", sum);
    return 0;
}