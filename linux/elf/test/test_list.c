#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct A {
    int x1;
    char x2;
};

int main()
{
    struct list_head *list;
    struct A a;

    list_init(&list);
    assert(list_is_empty(list));

    for (int i = 0; i < 10000; ++i) {
        list_add_tail(list, &i, sizeof(i));
    }

    getchar();

    struct list_node *cur;
    FOR_EACH(list, cur)
        printf("%d\n", *(int*)cur->item);

    list_free(list);
    free(list);

    return 0;
}
