#include <stdio.h>
#include <stddef.h>

struct A {
    int x1;
    char x2;
    double x3;
    void *op;
};

int main()
{
    printf("offset of x1: %lu\n", (size_t)&((struct A *)(NULL))->x1);
    printf("offset of x2: %lu\n", (size_t)&((struct A *)(NULL))->x2);
    printf("offset of x3: %lu\n", offsetof(struct A, x3));

    return 0;
}
