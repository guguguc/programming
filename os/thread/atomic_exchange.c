#include <stdio.h>
#include "atomic_exchange.h"

// atomic load and store
int xchg(volatile int *addr, int newval)
{
    int result;
    asm volatile ("lock xchg %0, %1" : "+m"(*addr), "=a"(result) : "1"(newval));
    return result;
}

void test()
{
    int a = 1, b = 2;
    int ans = xchg(&a, b);
    printf("%d\n", ans);
}
