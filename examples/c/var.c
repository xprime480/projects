
#include <stdio.h>
#include <stdarg.h>

double f(int c, ...)
{
  va_list ap;
  va_start(ap, c);
  double s = 0.0;
  int i;
  for ( i = 0 ; i < c ; ++i) {
    s += va_arg(ap, double);
  }
  va_end(ap);
  return s;
}


int main(int argc, char ** argv)
{
  double d1 = 1, d2 = 2, d3 = 3;
  fprintf(stdout, "%f\n", f(3, d1, d2, d3));
  fprintf(stdout, "%f\n", f(0, d1, d2, d3));
}
