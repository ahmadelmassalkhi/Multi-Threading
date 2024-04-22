#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct Factorial {
    int number;
    int factorial;
} Factorial;

void *factorial(void* arg) {
    Factorial *f = (Factorial *) arg;

    pthread_mutex_lock(&mutex);
    f->factorial = 1;
    for (int i = 2; i <= f->number; i++) f->factorial *= i;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    Factorial f;
    f.number = 7;

    pthread_t factorial_tid;
    pthread_create(&factorial_tid, NULL, factorial, (void*) &f);
    pthread_join(factorial_tid, NULL);

    printf("Factorial of %d = %d\n", f.number, f.factorial);
    return 0;
}