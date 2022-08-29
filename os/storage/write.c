#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define FILENAME "test.txt"
#define WRITE_CNT 10

size_t write2file(const char *filename)
{
  const char payload[] = "aaaaaaaaaa";
  int fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
  // int fd = open(FILENAME, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  assert(fd != -1);
  int len = strlen(payload);
  int total_len = len * WRITE_CNT;
  int cnt = 0;
  for (int i = 0; i < WRITE_CNT; ++i) {
    int bytes_written = write(fd, payload, len);
    cnt += bytes_written;
  }
  printf("writen to file %s %d bytes\n", filename, total_len);
  assert(cnt == total_len);
  close(fd);
  return total_len;
}

int main()
{
  write2file(FILENAME);
  return 0;
}
