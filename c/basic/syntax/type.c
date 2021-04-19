#include <stdio.h>

int main()
{
    char buff[256];
    char *ptr = buff;

    // 256
    printf("size of buff is %lu\n", sizeof(buff));
    // 6
    printf("size of str is %lu\n", sizeof("hello"));
    // 8
    printf("size of ptr to buff is %lu\n", sizeof(ptr));

    return 0;
}
