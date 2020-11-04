#include <stdio.h>

void print_permutation(int n, char prefix)
{
    if (n <= 0) return;
    for (int i = 0; i < n; ++i) {
        printf("%c%d", prefix, i);
    }
}

int main()
{
    print_permutation(10, 'p');
    return 0;
}
