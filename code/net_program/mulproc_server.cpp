#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class CTcpServer
{
public:
  int m_listenfd;
  int m_clientfd;

  CTcpServer() : m_clientfd(0), m_listenfd(0) {  }
  ~CTcpServer();

  bool InitServer(int port);
  bool Accept();
  int Send(const void *buf, const int buflen);
  int Recv(void *buf, const int buflen);

  void CloseClient();
  void CloseListen();
};

CTcpServer tcp_server;

int main(int argc, char *argv[])
{

}

bool
CTcpServer::InitServer(int port)
{
  if (m_listenfd != 0) {
    close(m_listenfd);
    m_listenfd = 0;
  }

  m_listenfd = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

}
