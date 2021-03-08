#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sched.h>
#include <time.h>

int main()
{
    unsigned long test = 10;
    unsigned long *addr=&test;

    unsigned char *page = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
            MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    assert(page != MAP_FAILED);
    printf("pid: %d\n", getpid());
    printf("addr: %p\n",page);
    getchar();

    pid_t pid = fork();
    unsigned char *ready = page;
    *ready = 0;

    if (pid == 0) {
        // child process
        {
            printf("[child ]: addr: %p\tvalue: %lu\n", addr, *addr);
            *addr = 0;
        }
        printf("[child ]: sleep 5 s\n");
        sleep(10);
        printf("[child ]: ready to write 1 to addr: %p\n", ready);
        *ready = 1;
        while (*ready != 2);
        printf("[child ]: parent write 2 to addr: %p\n", ready);
    } else {
        // parent process
        printf("[parent]: addr: %p\tvalue: %lu\n", addr, *addr);
        printf("[parent]: waiting for child process write bytes\n");
        while (*ready != 1)
            sched_yield();
        printf("[parent]: child has writen 1 to addr: %p\n", ready);
        printf("[parent]: sleep 5 s\n");
        printf("[parent]: ready to write 2 to addr %p\n", ready);
        *ready  = 2;
        sleep(5);
        {
            printf("[parent]: addr: %p\tvalue: %lu\n", addr, *addr);
        }
    }

    return 0;
}
