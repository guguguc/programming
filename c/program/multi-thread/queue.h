#ifndef _QUEUE_H
#define _QUEUE_H


#define MAX_SIZE 100

typedef struct queue queue_t;

struct queue {
    int queue[MAX_SIZE];
    int front;
    int size;
};

void push_queue(queue_t *q, int data);
int pop_queue(queue_t *q);
int is_full(queue_t *q);
int is_empty(queue_t *q);

#endif
