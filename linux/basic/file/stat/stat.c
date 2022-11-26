#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "please input file name\n");
    exit(1);
  }
  const char *filename = argv[1];
  struct stat buf;
  if (stat(filename, &buf) == -1) {
    perror("stat");
    exit(1);
  }
  switch (buf.st_mode & S_IFMT) {
  case S_IFREG:
    printf("reg file\n");
    break;
  case S_IFDIR:
    printf("directory\n");
    break;
  case S_IFSOCK:
    printf("socket\n");
    break;
  case S_IFLNK:
    printf("symbolic link\n");
    break;
  case S_IFIFO:
    printf("named pipe\n");
    break;
  case S_IFBLK:
    printf("block device\n");
    break;
  case S_IFCHR:
    printf("charactor device\n");
    break;
  }
  return 0;
}
