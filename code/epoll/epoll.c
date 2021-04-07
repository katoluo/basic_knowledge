#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define EPOLL_SIZE 100

void error_handing(char *message);


int main(int argc, char *argv[])
{
  int i, j, maxi;
  int lfd, cfd, efd;
  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_addr_sz;
  struct epoll_event event, *ep_event;
  int client[EPOLL_SIZE];

  if (argc != 2) {
    printf("Usage: %s <PORT>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  lfd = socket(PF_INET, SOCK_STREAM, 0);
  if (lfd == -1)
    error_handing("socket error");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family      = AF_INET;
  serv_addr.sin_port        = htons(atoi(argv[1]));
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  int optval = 1;
  setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, (void*)&optval, sizeof(optval));

  if (bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    error_handing("bind error");

  if (listen(lfd, 20) == -1)
    error_handing("listen error");

  for (i = 0; i != EPOLL_SIZE; ++i)
    client[i] = -1;
  maxi = -1;

  ep_event = (struct epoll_event*)malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
  efd = epoll_create(EPOLL_SIZE);
  if (efd == -1)
    error_handing("epoll_create error");
  event.events = EPOLLIN;
  event.data.fd = lfd;
  epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &event);


  return EXIT_SUCCESS;
}


void error_handing(char *message)
{
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(EXIT_FAILURE);
}
