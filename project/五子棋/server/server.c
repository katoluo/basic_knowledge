#include "../inc/gomoku.h"
#include "./my_socket.h"
#define   IP      "127.0.0.1"
#define   PORT    8888

static gomoku_show(char gomuku[][10])
{
  int i, j;
  for (i = 0; i < N; ++i) {
      for (j = 0; j < N; ++j) {
          printf("%c ", gomuku[i][j]);
      }
      printf("\n");
  }
}

static void gomuku_init(char gomuku[][10]) {
  int i, j;
  for (i = 0; i < N; ++i) {
      for (j = 0; j < N; ++j) {
          gomuku[i][j] = '_';
      }
  }
  for (i = 0; i < N; ++i) {
      gomuku[0][i] = gomuku[i][0] = (i + '0');
  }
}

int checkFive1(int x, int y, char gomoku[N][N]);
int main(void)
{
  int 
}
