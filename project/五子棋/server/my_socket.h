#ifndef __MY_SOCKET_H__
#define __MY_SOCKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define IN
#define OUT
#define MY_TCP  1
#define MY_UDP  2
typedef struct sockaddr* pSA;
typedef struct sockaddr_in SA;
#define ASSERT(flag, msg) ((flag) ? NULL:(fprintf(stdout, (msg)), exit(EXIT_FAILURE)))

void my_socketCli(int *fd_socket, int type, char *ip, int port, SA *my_addr);
void my_connect(int fd_socket, pSA server_addr, socklen_t addrlen); // tcp客户端连接服务器
void my_socketSer(int *fd_socket, int type, char *ip, int port);
void my_listen(int fd_socket, int listen_num);  // tcp 中服务器端一定别忘了listen
void my_accept(int *fd_client, int fd_socket, pSA client_addr, socklen_t *addrlen);
void my_send(int *sendlen, int fd_socket, int *msg, int len);
void my_recv(int *recvlen, int fd_socket, int *msg, int len);
void my_sendto(int *send_num, int fd_socket, int *msg, int len, pSA server_addr, socklen_t addrlen);
void my_recvfrom(int *recv_num, int fd_socket, int *msg, int len, pSA client_addr, socklen_t *addrlen);
void my_close(int fd_socket);

#endif
