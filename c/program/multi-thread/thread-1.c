#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>

#include "queue.h"


// generate a rand num in [min, max]
int gen_rand(int min, int max)
{
    return (rand() % (max-min)) + min;
}

void* produce(void *q)
{
    while (!is_full(q)) {
        int elem = gen_rand(0, MAX_SIZE-1);
        push_queue((queue_t*)q, elem);
        fprintf(stderr, "\e[01;32m[*] push %d to queue \x1b[0m\n", elem);
    }
    return NULL;
}

void* consume(void *q)
{
    while (!is_empty(q)) {
        int elem = pop_queue((queue_t*)q);
        fprintf(stderr, "\e[01;31m[*] pop %d in queue \x1b[0m\n", elem);
    }
    return NULL;
}

int main()
{
    queue_t q = {{0}, 0, 0};

    pthread_t t1, t2;
    pthread_create(&t1, NULL, produce, &q);
    pthread_create(&t2, NULL, consume, &q);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
