#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/epoll.h>
#define BUF_SIZE 4
#define EPOLL_SIZE 50
void error_handing(char *message);

int main(int argc, char *argv[])
{
  int lfd, cfd, epfd;
  struct sockaddr_in serv_addr, clnt_addr;
  struct epoll_event event, *ep_event;
  socklen_t addr_sz;
  int str_len, i, event_cnt;
  char buf[BUF_SIZE];

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  lfd = socket(PF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));
  if (bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    error_handing("bind() error");
  if (listen(lfd, 5) == -1)
    error_handing("listen() error");

  epfd = epoll_create(EPOLL_SIZE);
  ep_event = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

  event.events = EPOLLIN;
  event.data.fd = lfd;
  epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &event);

  while (1) {

    event_cnt = epoll_wait(epfd, ep_event, EPOLL_SIZE, -1);
    if (event_cnt == -1) {
      puts("epoll_wait() error");
      break;
    }

    puts("return epoll_wait");
    for (i = 0; i != event_cnt; ++i) {
      if (ep_event[i].data.fd == lfd) {
        addr_sz = sizeof(clnt_addr);
        cfd = accept(lfd, (struct sockaddr*)&clnt_addr, &addr_sz);
        event.events = EPOLLIN;
        event.data.fd = cfd;
        epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &event);
        printf("connected client: %d\n", cfd);
      }
      else {
        str_len = read(ep_event[i].data.fd, buf, sizeof(buf));
        if (str_len == 0) {
          epoll_ctl(epfd, EPOLL_CTL_DEL, ep_event[i].data.fd, NULL);
          close(ep_event[i].data.fd);
          printf("closed client: %d\n", ep_event[i].data.fd);
        }
        else {
          write(ep_event[i].data.fd, buf, str_len);
        }
      }
    }
  }

  close(lfd);
  close(epfd);
  return EXIT_SUCCESS;
}

void error_handing(char *message)
{
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(EXIT_FAILURE);
}
