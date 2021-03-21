#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(void);

int main(int argc, char *argv[])
{
  if ( argc != 2 ) {
    printf("Usage: %s <IP> <port> \n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int lfd, cfd, state;
  struct sockaddr_in serv_addr, clnt_addr;
  struct sigaction act;
  socklen_t sz;

  act.sa_restorer = read_childproc;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  state = sigaction(SIGCHLD, &act, NULL);

  lfd = socket(PF_INET, SOCK_STREAM, 0);

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(atoi(argv[1]));
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

  listen(lfd, 5);

  while (1) {
    char ip_str[32];
    sz = sizeof(clnt_addr);
    cfd = accept(lfd, (struct sockaddr*)&clnt_addr, &sz);
    if ( cfd == -1 )
      continue;
    else
      printf("新连接：IP[%s] PORT[%d] \n",
          inet_ntoa(clnt_addr.sin_addr),
          clnt_addr.sin_port);
    
    pid_t pid = fork();
    if ( pid < 0 ) {
      close(cfd);
      continue;
    }
    else if ( pid == 0 ) {

      // 子进程不需要lfd
      close(lfd);
      char buf[1024];
      int len;
      while (( len = read(cfd, buf, sizeof(buf))) != 0)
        write(cfd, buf, len);

      printf("断开连接：IP[%s] PORT[%d] \n",
          inet_ntoa(clnt_addr.sin_addr),
          clnt_addr.sin_port);
      close(cfd);
    }
    else
      close(cfd);
  }

  close(lfd);
  return EXIT_SUCCESS;
}

void read_childproc(void)
{
  pid_t pid;
  int status;
  pid = waitpid(-1, &status, WNOHANG);
  printf("remove proc id: %d \n", pid);
}
