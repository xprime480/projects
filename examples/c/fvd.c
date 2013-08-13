
#include <stdio.h>
#include <math.h>


int main(int argc, char **argv)
{
  double d = 1.0 / 3.0;
  float  f = d;
  double x = f;
  float  y = x;

  if ( f == d ) {
    printf("equal\n");
  } 
  else {
    printf("u lose\n");
  }

  if ( fabs(f-d) <- 1e-10 ) {
    printf("close enough\n");
  } 

  printf("%g\n", (f-d));
  printf("%g\n", (x-d));
  printf("%g\n", (y-f));

  return 0;
}
