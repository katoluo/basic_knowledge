#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("Usage: %s <IP> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int fd;
  char buf[1024];
  struct sockaddr_in addr;

  fd = socket(PF_INET, SOCK_STREAM, 0);

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[2]));
  addr.sin_addr.s_addr = htonl(atoi(argv[1]));

  connect(fd, (struct sockaddr*)&addr, sizeof(addr));

  while (1) {
    fgets(buf, sizeof(buf), stdin);
    write(fd, buf, strlen(buf));
    read(fd, buf, sizeof(buf));
  }

  close(fd);
  return EXIT_SUCCESS;
}
