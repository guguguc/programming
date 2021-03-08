#include "demo-1.h"

extern int i;
extern const int k;
extern void disp_addr(const void *obj, const char *str);

void nop(void)
{
    disp_addr(&i, "i'");
    disp_addr(&k, "k'");
}
