#include <stdio.h>
#include "list.h"

#define N 9

void print(ptr_dnode head)
{
    ptr_dnode p = head;
    while (p) {
        printf("%d ", get_elem(p));
        p = dpre(p);
    }
    printf("\n");
}

void pretty_print(ptr_dnode head)
{
    ptr_dnode p = dnext(head);
    size_t count = 0;
    while (p) {
        printf("%2ld current:%p\tnext:%p\tpre:%p data:%d\n",
               count++,p, dnext(p), dpre(p), get_elem(p));
        p = dnext(p);
    }
}

int main()
{
    int a[N] = {1, 2, 3, 4, 5, 6, 2, 3, 4};
    ptr_dnode root, p;
    root = create_dnode(-1);
    p = root;
    for (int i = 0; i < N; ++i) {
        p = insert_node(p, i);
    }
    pretty_print(root);
    ptr_dnode node = find_node(root, 2);
    return 0;
}