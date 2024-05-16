#include <stdio.h>
#include <omp.h>

const long long nbOfRectangles = 100000000; // the larger, the more accurate

/*
    a : lower bound
    b : upper bound
    f : function
*/
double Integral_Parallel(double a, double b, double f(double)) {
    double dx = (b - a) / (double)nbOfRectangles;

    double sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for(long long i = a + 1; i <= nbOfRectangles; i++) sum += f(i * dx) * dx;

    return sum;
}

double function(double x) {
    return (4.0) / (1 + x * x);
}

int main() {
    double start = omp_get_wtime();
    printf("PI = %lf\n", Integral(0, 1, function));
    printf("Parallel = %lf seconds\n\n", omp_get_wtime() - start);
    
    return 0;
}

