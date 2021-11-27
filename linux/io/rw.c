#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/uio.h>

#define buf_size ((size_t)1 << 30)

const char *filename = "/opt/download/win10.iso";
uint8_t *buff;
int fd;
int ret;

void warm_up()
{
    buff = malloc(buf_size);
    memset(buff, 0, buf_size);
    fd = open(filename, O_RDONLY);
    assert(fd > 0);
    // srand(time(NULL));
    // for (size_t i = 0; i < buf_size; ++i)
    //     buff[i] = rand();
}

void clean_up()
{
    close(fd);
    free(buff);
}

void read_t()
{
    ret = read(fd, buff, buf_size);
    assert(ret == buf_size);
}

void readv_t()
{
    struct iovec iov;
}

void io_uring_t()
{

}

void mmap_t()
{

}

void run()
{
    read_t();
}

int main()
{
    warm_up();
    run();
    clean_up();

    return 0;
}
