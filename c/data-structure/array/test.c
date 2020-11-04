#include <stdio.h>
#include "list.h"

void print_list(head l)
{
    ptr_node p = next(l);
    while (p) {
        printf("%d ", get_data(p));
        p = next(p);
    }
    printf("\n");
}

int main()
{
    int a[] = {1, 2, 2, 3, 3 ,4 ,5, 6, 7, 8, 9, 10};
    int n = 10;
    head l = create_list();
    for (int i = 0; i < n; ++i)
        append(l, a[i]);
    print_list(l);
    remove_all(l, 2);
    print_list(l);
    return 0;
}