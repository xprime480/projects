
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <cstdio>

using namespace std;

void f()
{
  sleep(10);
}

int main(int argc, char ** argv)
{
  struct timeval tvStart;
  struct timeval tvEnd;

  gettimeofday(&tvStart, 0);
  f();
  gettimeofday(&tvEnd, 0);
  
  unsigned seconds;
  unsigned useconds;

  if ( tvEnd.tv_usec >= tvStart.tv_usec ) {
    seconds  = tvEnd.tv_sec  - tvStart.tv_sec;
    useconds = tvEnd.tv_usec - tvStart.tv_usec;
  }
  else {
    seconds  = -1      + tvEnd.tv_sec  - tvStart.tv_sec;
    useconds = 1000000 + tvEnd.tv_usec - tvStart.tv_usec;
  }

  fprintf(stdout, "Work took %d seconds, %d microseconds", seconds, useconds);

  return 0;
}
