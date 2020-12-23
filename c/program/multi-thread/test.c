#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

void test_queue()
{
    queue_t q = {{0}, 0, 0};
    for (int i = 0; !is_full(&q); ++i)
        push_queue(&q, i);

    for (int i = 0; !is_empty(&q); ++i)
        assert(pop_queue(&q) == i);
}

