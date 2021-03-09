#include "list.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

void _cnt_incre(plist_t list) {
    list->count += 1;
}

static inline void node_init(pnode_t *pnode)
{
    printf("[node init inner]: %p\n", pnode);
    *pnode = malloc(sizeof(struct list_node));
    assert(*pnode != NULL);
    printf("[node after inner]: %p\n", pnode);
    memset(*pnode, 0, sizeof(struct list_node));
}

void node_init_copy(pnode_t *pnode,
        const void *data, size_t size)
{
    printf("[node init]: %p\n", pnode);
    node_init(pnode);
    void *_data = malloc(size);
    printf("[data]: %p\n", _data);
    memcpy(_data, data, size);
    (*pnode)->item = _data;
}

void node_init_move(pnode_t *pnode, void *data)
{
    node_init(pnode);
    (*pnode)->item = data;
}


void list_init(plist_t *plist)
{
    struct list_node *fhead, *ftail;

    node_init(&fhead); node_init(&ftail);
    fhead->next = ftail; fhead->prev = ftail;
    ftail->next = fhead; ftail->prev = fhead;

    *plist = malloc(sizeof(struct list_head));
    printf("[list]: %p\n", *plist);
    (*plist)->count = 0;
    (*plist)->fhead = fhead;
    (*plist)->ftail = ftail;
}

void list_init_by_buff(plist_t *plist,
        char *buf, size_t buf_size, size_t ent_size)
{
    list_init(plist);
    size_t nums = buf_size / ent_size;
    printf("nums: %lu\n", nums);
    printf("buf size: %lu\n", buf_size);
    printf("ent size: %lu\n", ent_size);
    printf("buf: %p\n", buf);
    getchar();
    for (size_t i = 0; i < nums; ++i) {
        printf("%lu\n", i * ent_size);
        list_add_tail(*plist, buf + i * ent_size, ent_size);
        printf("%lu\n", i);
    }
}

void list_add_tail(plist_t list, const void *data, size_t size)
{
    printf("[size] %lu\n", size);
    struct list_node *node = NULL;
    printf("[before] %p\n", node);
    printf("[buff] %p\n", data);
    node_init_copy(&node, data, size);
    printf("[after] %p\n", node);
    node->prev = list->ftail->prev;
    node->next = list->ftail;
    list->ftail->prev->next = node;
    list->ftail->prev = node;
    _cnt_incre(list);
}

void list_add_head(plist_t list, void *data, size_t size)
{
    struct list_node *node;
    node_init_copy(&node, data, size);
    node->next = HEAD(list);
    node->prev = list->fhead;
    HEAD(list)->prev = node;
    HEAD(list) = node;
    _cnt_incre(list);
}

void list_del(plist_t list, size_t pos)
{
    assert(!list_is_empty(list));
}

void list_del_tail(plist_t list)
{
    return;
}

void list_del_head(plist_t list)
{
    return;
}

void list_clear(plist_t list)
{
    struct list_node *cur, *tmp;
    cur = HEAD(list);
    while (cur != TAIL(list)) {
        tmp = cur->next;
        free(cur->item);
        free(cur);
        cur = tmp;
    }
}

pnode_t list_get(plist_t list, size_t pos)
{
    pnode_t cur = HEAD(list);
    for (size_t i = 0; cur != TAIL(list) && i < pos; ++i)
        cur = cur->next;
    return cur == TAIL(list) ? NULL : cur;
}

void list_free(plist_t *list)
{
    list_clear(*list);
    free((*list)->fhead);
    free((*list)->ftail);
    free(*list);
}

int list_is_empty(plist_t list)
{
    return HEAD(list) == TAIL(list);
}

static inline size_t list_count(plist_t list)
{
    return list->count;
}

