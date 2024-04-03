#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define Buffer_Limit 10

int Buffer_Index_Value = 0;
char *Buffer_Queue;

void *Consumer()
{
      while (1)
      {
            printf("Consumer:%d\n", Buffer_Index_Value--);
      }
}

void *Producer()
{
      while (1)
      {
            Buffer_Queue[Buffer_Index_Value++] = '@';
            printf("Producer:%d\n", Buffer_Index_Value);
      }
}

int main()
{
      pthread_t producer_thread_id, consumer_thread_id;
      Buffer_Queue = (char *)malloc(sizeof(char) * Buffer_Limit);

      // create threads
      pthread_create(&producer_thread_id, NULL, Producer, NULL); 
      pthread_create(&consumer_thread_id, NULL, Consumer, NULL);

      // wait threads to finish
      pthread_join(producer_thread_id, NULL);
      pthread_join(consumer_thread_id, NULL);

      return 0;
}