#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define Buffer_Limit 100
#define CHUNK_SIZE 5

int Buffer_Index_Value = 0;
char *Buffer_Queue;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
int producers_turn = 1;

void *Consumer()
{
    while (1)
    {
        // lock
        pthread_mutex_lock(&mutex);

        // while producers_turn, wait until buffer is full (until they are done)
        while(producers_turn) {
            pthread_cond_wait(&full, &mutex);
        }

        // consume CHUNK_SIZE elements
        int i = 0;
        while(i++ < CHUNK_SIZE && Buffer_Index_Value > 0) {
            printf("Consumer:%d\n", Buffer_Index_Value--);
        }

        // signal when buffer is empty
        if(Buffer_Index_Value == 0) {
            pthread_cond_signal(&empty);
            producers_turn = 1;
        } else {
            pthread_cond_signal(&full); // wakeup one consumer
            pthread_cond_wait(&full, &mutex); // wait for another consumer (or a producer) to wake me up
        }

        // unlock
        pthread_mutex_unlock(&mutex);
    }
}

void *Producer()
{
    while (1)
    {
        // lock
        pthread_mutex_lock(&mutex);

        // while consumers_turn, wait until buffer is empty (until they are done)        
        while(!producers_turn) pthread_cond_wait(&empty, &mutex);

        // produce CHUNK_SIZE elements
        int i = 0;
        while(i++ < CHUNK_SIZE && Buffer_Index_Value < Buffer_Limit) {
            Buffer_Queue[Buffer_Index_Value++] = '@';
            printf("Producer:%d\n", Buffer_Index_Value);
        }

        // signal when buffer is full
        if(Buffer_Index_Value == Buffer_Limit) {
            pthread_cond_signal(&full);
            producers_turn = 0;
        } else {
            pthread_cond_signal(&empty); // wake one producer
            pthread_cond_wait(&empty, &mutex); // wait for another producer (or a consumer) to wake me up
        }

        // unlock
        pthread_mutex_unlock(&mutex);
    }
}


# define N 10

int main()
{
    // initialize
    pthread_t producers[N];
    pthread_t consumers[N];
    Buffer_Queue = (char *)malloc(sizeof(char) * Buffer_Limit);

    // create consumers
    for(int i = 0; i < N; i++) {
        pthread_create(&producers[i], NULL, Producer, NULL);
        pthread_create(&consumers[i], NULL, Consumer, NULL);
    }
    
    // wait threads to finish
    for(int i = 0; i < N; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    // free resources
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}