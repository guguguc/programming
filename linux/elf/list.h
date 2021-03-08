#ifndef __LIST__
#define __LIST__

#include <sys/types.h>

struct list_head {
    void *item;
    struct list_head *next, *prev;
};

struct list_head *create_list(const char *buf, size_t buf_size,
        size_t ent_size);
void add_to_list(struct list_head *list, void *data);
void free_list(struct list_head *list);


#endif
