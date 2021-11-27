#include <stdio.h>
#include <stdlib.h>


int main()
{
    int *a = NULL;
    int **pa = &a;
    *pa = malloc(sizeof(int));
    **pa = 10;

    printf("%d\n", *a);
    free(a);

    return 0;
}
