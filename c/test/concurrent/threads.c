#include <pthread.h>
#include <stdio.h>

void count(void)
{
    for (int i = 0; i < 10; ++i)
        printf("count %d\n", i);
}

int main()
{
    pthread_t pid;
    int err = pthread_create(&pid, NULL, (void*)count, NULL);
    return 0;
}
