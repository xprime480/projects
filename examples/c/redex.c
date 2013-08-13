#define _GNU_SOURCE

#include <stdio.h>
#include <time.h>
#include <sys/time.h>


int main(int argc, char ** argv)
{
  struct timespec tp;
  int k = clock_gettime(0, &tp);
  printf("%d\n", k);
  return 0;
}
