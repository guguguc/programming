#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>

#define check_error(ret)                                                       \
  if (ret == -1) {                                                             \
    perror(NULL);                                                              \
    return 1;                                                                  \
  }

int main(int argc, const char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <filename>\n", argv[0]);
    return 1;
  }
  fprintf(stdout, "[pid] %d started\n", getpid());
  getchar();
  int ret, fd, fk;
  const char *fn = argv[1];
  fd = open(fn, O_RDONLY);
  check_error(fd) fk = flock(fd, LOCK_SH | LOCK_NB);
  check_error(fk) fprintf(stdout, "succeed to flock fd %d\n", fd);
  getchar();
  ret = flock(fd, LOCK_UN);
  check_error(ret);
  fprintf(stdout, "succeed to unflock fd %d\n", fd);
  close(fd);
  return 0;
}
