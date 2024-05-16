#include <stdio.h>

static long num_steps = 100;
double step;


int main() {
    double pi = 0;
    step = 1.0 / (double)num_steps;
    int i;
    double x, sum;
    for (i = 0, sum = 0.0; i < num_steps; i = i + 1) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    pi += sum * step;
    printf("Value of PI: %f\n", pi);
    return 0;
}
