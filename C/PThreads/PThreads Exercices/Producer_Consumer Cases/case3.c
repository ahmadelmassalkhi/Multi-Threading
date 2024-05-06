#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define Buffer_Limit 100
#define CHUNK_SIZE 5

int Buffer_Index_Value = 0;
char *Buffer_Queue;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t notFull = PTHREAD_COND_INITIALIZER;

void *Consumer()
{
    while (1)
    {
        // lock
        pthread_mutex_lock(&mutex);

        // while empty, wait until there is something to consume
        while(Buffer_Index_Value == 0) pthread_cond_wait(&notEmpty, &mutex);

        // consume one CHUNK
        int i = 0;
        while(i++ < CHUNK_SIZE && Buffer_Index_Value > 0) printf("Consumer:%d\n", Buffer_Index_Value--);
        
        // we just consumed elements => definitely not full
        pthread_cond_signal(&notFull);

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
        
        // while full, wait until there is space to produce
        while(Buffer_Index_Value == Buffer_Limit) pthread_cond_wait(&notFull, &mutex);

        // produce one CHUNK
        int i = 0;
        while(i++ < CHUNK_SIZE && Buffer_Index_Value < Buffer_Limit) {
            Buffer_Queue[Buffer_Index_Value++] = '@';
            printf("Producer:%d\n", Buffer_Index_Value);
        }

        // we just produced elements => definitely not empty
        pthread_cond_signal(&notEmpty);

        // unlock
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    // initialize
    pthread_t producer_thread_id, consumer_thread_id;
    Buffer_Queue = (char *)malloc(sizeof(char) * Buffer_Limit);

    // create threads
    pthread_create(&consumer_thread_id, NULL, Consumer, NULL);
    pthread_create(&producer_thread_id, NULL, Producer, NULL);

    // wait threads to finish
    pthread_join(producer_thread_id, NULL);
    pthread_join(consumer_thread_id, NULL);

    return 0;
}