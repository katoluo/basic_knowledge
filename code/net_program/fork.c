#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{
  pid_t id;

  id = fork();
  if (id < 0)
    exit(1);
  else if (id > 1) {
    printf("I am parent process, pid: %d\n", getpid());
    for (int i = 0; i != 10; ++i) {
      printf("%d\n", i);
      sleep(1);
    }
    exit(0);
  }
  else {
    printf("I am child process, pid: %d\n", getpid());
    for (int j = 0; j != 10; ++j) {
      printf("%d\n", j);
      exit(0);
    }
  }
}
