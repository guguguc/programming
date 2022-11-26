#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define BUFF_SIZE 1024

int main()
{
    int status, pid;
    char buf[BUFF_SIZE];
    printf("%% ");
    while (fgets(buf, BUFF_SIZE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0;
        }
        if ((pid = fork()) < 0) {
            goto err_exit;
        // child
        } else if (pid == 0) {
            if ( execlp(buf, NULL) == -1) {
                printf("couldn't execute command:%s\n", buf);
                perror("error reason");
                exit(127);
            }
        // parent
        } else {
            if (waitpid(pid, &status, 0) < 0) {
                goto err_exit;
            }
        }
        printf("%% ");
    }
  return 0;

err_exit:
    perror("error msg:");
    exit(1);
}
