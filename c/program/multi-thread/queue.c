#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void push_queue(queue_t *q, int data)
{
    if (q->size == MAX_SIZE) {
        fprintf(stderr, "err: push data to a full queue!");
        exit(1);
    }
    q->queue[(q->front + q->size) % MAX_SIZE] = data;
    q->size++;
}

int pop_queue(queue_t *q)
{
    if (!q->size)
        return -1;
    int elem = q->queue[q->front];
    q->front = (++q->front) % MAX_SIZE;
    q->size--;
    return elem;
}

int is_empty(queue_t *q)
{
    return q->size == 0;
}

int is_full(queue_t *q)
{
    return q->size == MAX_SIZE;
}
