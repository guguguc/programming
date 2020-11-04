#include "list.h"


struct dlist {
    elem data;
    struct dlist *next;
    struct dlist *pre;
};

ptr_dnode create_node(elem data)
{
    ptr_dnode node = (ptr_dnode) malloc(sizeof(struct dlist));
    node->data = data;
    node->next = NULL;
    node->pre = NULL;
    return node;
}

// insert after node
ptr_dnode insert_node(ptr_dnode node, elem data)
{
    ptr_dnode new_node = create_node(data);
    if (node->next)
        node->next->pre = new_node;
    new_node->next = node->next;
    new_node->pre = node;
    node->next = new_node;
    return new_node;
}

// remove current node
// return removed node if success else NULL
ptr_dnode remove_node(ptr_dnode node)
{
    if (!node || !node->pre)
        return NULL;
    if (node->next)
        node->next->pre = node->pre;
    node->pre->next = node->next;
    return node;
}

ptr_dnode find_node(ptr_dnode node, elem data)
{
    if (!node) {
        return NULL;
    } else if (node->data == data) {
        return node;
    } else {
        ptr_dnode target = find_node(node->next, data);
        return target ? target : find_node(node->pre, data);
    }
}

ptr_dnode find_next(ptr_dnode node, elem data)
{
    if (!node) return NULL;
    ptr_dnode p = node->next;
    while (p) {
        if (p->data == data)
            return p;
        p = p->next;
    }
    return p;
}

ptr_dnode find_prior(ptr_dnode node, elem data)
{
    if (!node) return NULL;
    ptr_dnode p = node->next;
    while (p) {
        if (p->data == data)
            return p;
        p = p->pre;
    }
    return p;
}

elem get_elem(ptr_dnode node)
{
    return node->data;
}

ptr_dnode dnext(ptr_dnode node)
{
    if (!node)
        return NULL;
    return node->next;
}

ptr_dnode dpre(ptr_dnode node)
{
    if (!node)
        return NULL;
    return node->pre;
}