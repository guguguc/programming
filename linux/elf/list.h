#ifndef __LIST__
#define __LIST__

#include <sys/types.h>
#include <stdint.h>

typedef struct list_head list_t;
typedef struct list_head *plist_t;
typedef struct list_node node_t;
typedef struct list_node *pnode_t;

#define HEAD(name) ((name)->fhead->next)

#define TAIL(name) ((name)->ftail)

#define FOR_EACH(list, cur) \
    for(cur = HEAD(list); cur != TAIL(list); cur=cur->next)

struct list_node {
    void *item;
    size_t size;
    struct list_node *next, *prev;
};

struct list_head {
    size_t count;
    struct list_node *fhead, *ftail;
};

void list_init(plist_t *plist);

void list_init_by_buff(plist_t *plist,
        char *buf, size_t buf_size, size_t ent_size);

void list_add_tail(plist_t list, const void *data, size_t size);

void list_add_head(plist_t list, void *data, size_t size);

int list_is_empty(plist_t list);

void list_free(plist_t *list);

pnode_t list_get(plist_t list, size_t pos);

pnode_t list_get_by_off(plist_t list, off_t off);

static inline size_t list_count(plist_t list)
{
    return list ? list->count : 0;
}

#endif
