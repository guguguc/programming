#include "list.h"

struct list
{
    elem data;
    struct list *next;
};

head create_list(void)
{
    head root = (head) malloc(sizeof(list));
    root->data = 0;
    root->next = NULL;
    return root;
}

ptr_node create_node(elem data)
{
    ptr_node node = (ptr_node) malloc(sizeof(list));
    node->data = data;
    node->next = NULL;
    return node;
}

head create_list_by_array(elem *array, int length)
{
    if (length <= 0 || !array)
        return NULL;
    head root = (head) malloc(sizeof(list));
    ptr_node p = root;
    for (int i = 0; i < length; ++i) {
        p->next = create_node(array[i]);
        p = p->next;
    }
    root->data = length;
    return root;
}

int insert(head list, elem data, int position)
{
    if (position < 0 || position >= list->data)
        return 1;
    ptr_node p = list;
    int counter = 0;
    while (p->next && ++counter < position)
        p = p->next;
    ptr_node node = create_node(data);
    node->next = p->next;
    p->next = node;
    list->data++;
    return 0;
}

int append(head list, elem data)
{
    ptr_node p = list;
    while (p->next)
        p = p->next;
    p->next = create_node(data);
    return p->next ? 0 : 1;
}

int remove_data(head list, elem data)
{
    ptr_node pre_node = find_pre(list, data);
    if (!pre_node) return 1;
    pre_node->next = pre_node->next->next;
    list->data--;
    return 0;
}

int remove_all(head list, elem data)
{
    int ret = remove_data(list, data);
    while (!ret)
        ret = remove_data(list, data);
    return ret;
}

int find(head list, elem data)
{
    ptr_node p = list->next;
    int index = 0;
    while (p && p->data != data) {
        p = p->next;
        index++;
    }
    return p ? index : -1;
}

int find_range(head list, int left, int right, elem data)
{
    int index = find(list+left-1, data);
    return (index == -1 || index >= right) ? -1 : index;
}

int free_list(head list)
{
    ptr_node p, q;
    p = q = list;
    while (q) {
        q = p->next;
        free(p);
        p = q;
    }
    return 0;
}

ptr_node find_pre(head list, elem data)
{
    ptr_node p = list;
    while (p->next && p->next->data != data)
        p = p->next;
    return p->next ? p : NULL;
}

ptr_node next(ptr_node node)
{
    return node->next;
}

elem get_data(ptr_node node)
{
    assert(node);
    return node->data;
}