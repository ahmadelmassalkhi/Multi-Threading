#include <stdio.h>
#include <pthread.h>




void * function() {
    // do something
    printf("hello world\n");
}


int main() {

    // define variables that will hold thread ids
    pthread_t id_1, id_2;

    // create threads
    pthread_create(&id_1, NULL, function, NULL); // &id, attr, func, args
    pthread_create(&id_2, NULL, function, NULL);

    // wait threads
    pthread_join(id_1, NULL);
    pthread_join(id_2, NULL);

    return 0;
}
