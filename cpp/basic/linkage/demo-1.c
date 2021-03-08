#include "demo-1.h"

extern int i;
extern int j;
extern void nop(void);

void disp_addr(const void *obj, const char *str)
{
    printf("addr of object %s: %p\n", str, obj);
    printf("value of object %s: %d\n", str, *((int*) obj));
}

int i = 1;

int main()
{
    disp_addr(&i, "i");
    disp_addr(&j, "j");
    disp_addr(&k, "k");

    nop();

    return 0;
}
