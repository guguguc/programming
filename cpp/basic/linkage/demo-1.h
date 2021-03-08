#ifndef _DEMO
#define _DEMO

#include <stdio.h>

extern int i;
static int j = 1;
const  int k = 1;

void disp_addr(const void *obj, const char *str);

#endif
