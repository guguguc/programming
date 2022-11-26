#include <stdio.h>
#include <pthread.h>

__thread char *base, *cur;
__thread int id;

__attribute__((noinline)) void set_cur(void *ptr) { cur = ptr; }
__attribute__((noinline)) char * get_cur() { return cur; }

void stackoverflow(int n )
{
    set_cur(&n);
    if (n % 1024 == 0)
    {
        int sz = base - get_cur();
        printf("stack is of tid %d >= %d KB\n", id, sz / 1024);
    }
    stackoverflow(n + 1);
}

void probe(int tid)
{
    id = tid;
    base = (void*)&tid;
    stackoverflow(0);
}

void create(void *fn)
{
    pthread_t thread;
    int  i = 0;
    pthread_create(&thread, NULL, fn, &i);
    pthread_join(thread, NULL);
}

int main()
{
    setbuf(stdout, NULL);
    for (int i  = 0; i < 4; ++i)
    {
        create(probe);
    }
}
