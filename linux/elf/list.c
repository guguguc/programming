#include "list.h"
#include <stdlib.h>
#include <assert.h>

struct list_head *create_list(const char *buf, size_t buf_size,
        size_t ent_size)
{
    if (!buf || ent_size == 0 || (buf_size % ent_size))
        return NULL;

    size_t nums = buf_size / ent_size;
    for (size_t i = 0; i < nums; ++i)
}

void add_to_list(struct list_head *node, void *data)
{
    assert(node);
    node->next = malloc(sizeof(struct list_head));
    node->next->item = data;
    node->next->prev = node;
    node->next->next = NULL;
}

void free_list(struct list_head *list)
{

}
