#include "operation.h"
#include <stdio.h>

#define TEST_SQRT(x) printf("sqrt(%6lf) = %6lf\n", (x), sqrt_r(x))

int main()
{
    TEST_SQRT(4.0);
    TEST_SQRT(1.1);
    TEST_SQRT(-213.);
    TEST_SQRT(24.);
    TEST_SQRT(213.2);

    return 0;
}
