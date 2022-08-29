#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define FILENAME "test.txt"
#define WRITE_CNT 10
#define NTHREAD 2
int ps;

size_t write2file(const char *filename)
{
  pid_t pid = gettid();
  const char payload[] = "aaaaaaaaaa";
  int fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
  printf("[ %d ] file descriptor: %d\n", pid, fd);
  // int fd = open(FILENAME, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  assert(fd != -1);
  int len = strlen(payload);
  int total_len = len * WRITE_CNT;
  int cnt = 0;
  for (int i = 0; i < WRITE_CNT; ++i) {
    int bytes_written = write(fd, payload, len);
    cnt += bytes_written;
    // printf("[ %d ] writen to fd %d (%s) %d bytes\n", pid, fd, filename, len);
    if (ps) getchar();
  }
  printf("[ %d ] total writen to fd %d (%s) %d bytes\n", pid, fd, filename, total_len);
  assert(cnt == total_len);
  close(fd);
  return total_len;
}

int main(int argc, char *argv[])
{
   if (argc == 2 && !strcmp(argv[1], "-c"))
   {
       ps = 1;
   }
  // write2file(FILENAME);
  pthread_t t[NTHREAD];
  for (int i = 0; i < NTHREAD; ++i) {
    pthread_create(&t[i], NULL, (void*(*)(void*))(write2file), FILENAME);
  }
  for (int i = 0; i < NTHREAD; ++i) {
    pthread_join(t[i], NULL);
  }
  return 0;
}
