#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{

  fprintf(stdout, "ttyname(0): %s\n", ttyname(0));
  fprintf(stdout, "ttyname(1): %s\n", ttyname(1));
  fprintf(stdout, "ttyname(2): %s\n", ttyname(2));
  return 0;
}

