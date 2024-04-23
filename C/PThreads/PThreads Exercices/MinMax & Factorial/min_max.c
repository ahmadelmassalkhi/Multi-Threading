#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

typedef struct Array {
    int *array;
    int size;
    int min, max;
} Array;

Array init_Array(int size) {
    Array a;
    a.size = size;
    a.array = (int*)malloc(sizeof(int) * a.size);
    return a;
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*********************************************************/

void* find_max(void *arg) {
    Array *a = (Array *)arg;

    // synchronize block for accessing shared variables
    pthread_mutex_lock(&mutex);
    a->max = a->array[0];
    for (int i = 0; i < a->size; i++) {
        if (a->array[i] > a->max) a->max = a->array[i];
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* find_min(void *arg) {
    Array *a = (Array *)arg;

    // synchronize block for accessing shared variables
    pthread_mutex_lock(&mutex);
    a->min = a->array[0];
    for (int i = 0; i < a->size; i++) {
        if (a->array[i] < a->min) a->min = a->array[i];
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {

    // initialize array with random integers
    Array a = init_Array(10);
    srand(time(NULL));
    for (int i = 0; i < a.size; i++) a.array[i] = rand();

    pthread_t min_id, max_id;

    // create threads
    pthread_create(&max_id, NULL, find_max, (void*) &a);
    pthread_create(&min_id, NULL, find_min, (void*) &a);
    
    // wait threads
    pthread_join(max_id, NULL);
    pthread_join(min_id, NULL);

    // print results
    printf("Maximum value: %d\n", a.max);
    printf("Minimum value: %d\n", a.min);

    return 0;
}
