
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
  if ( argc > 1 && argv[1][0] != '-' ) {
    int f = open(argv[1], O_RDONLY);
    if ( f < 0 ) {
      perror("open input: ");
      return 1;
    }
    
    int g = dup2(f, 0);
    if ( g < 0 ) {
      perror("dup2 input: ");
      return 1;
    }
  }

  if ( argc > 2 && argv[2][0] != '-' ) {
    int f = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if ( f < 0 ) {
      perror("open output: ");
      return 1;
    }
    
    int g = dup2(f, 1);
    if ( g < 0 ) {
      perror("dup2 output: ");
      return 1;
    }
  }

  int c;
  while ( (c = getchar()) != EOF ) {
    putchar(c);
  }
  
}
