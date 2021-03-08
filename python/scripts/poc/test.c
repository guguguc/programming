#include <stdio.h>
#include <string.h>

void test_strtok(char *str, const char *delim)
{
  for (char *ptr = str;; ptr = NULL) {
    char *subtoken = strtok(ptr, delim);
    if (subtoken == NULL)
      break;
    printf("%s\n", subtoken);
    printf("%s\n", ptr);
    printf("1 addr: %p\n2 addr: %p\n", subtoken, ptr);
    break;
  }
  printf("end\n");
}

void test1()
{
  char str[] = "hello\r\nworld\r\nthis\r\nis\r\n";
  int len = strlen(str);
  test_strtok(str, "\r\n");
  printf("str is %s\n", str);
  for (int i = 0; i < len; ++i) {
    printf("c: %c\n", str[i]);
  }
}

int main()
{
  test1();

  return 0;
}
