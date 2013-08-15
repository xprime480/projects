#include <cstdio>


#include "mathutils.h"

int main(int, char**)
{
  fprintf(stderr, "%f\n", round_gamma(   0.9));
  fprintf(stderr, "%f\n", round_gamma(   0.97));
  fprintf(stderr, "%f\n", round_gamma(   0.975));
  fprintf(stderr, "%f\n", round_gamma(   0.9752));
  fprintf(stderr, "%f\n", round_gamma(   0.97523));
  fprintf(stderr, "%f\n", round_gamma(   1.97523));
  fprintf(stderr, "%f\n", round_gamma(  11.97523));
  fprintf(stderr, "%f\n", round_gamma( 125.97523));

  fprintf(stderr, "%f\n", round_gamma(-  0.9));
  fprintf(stderr, "%f\n", round_gamma(-  0.97));
  fprintf(stderr, "%f\n", round_gamma(-  0.975));
  fprintf(stderr, "%f\n", round_gamma(-  0.9752));
  fprintf(stderr, "%f\n", round_gamma(-  0.97523));
  fprintf(stderr, "%f\n", round_gamma(-  1.97523));
  fprintf(stderr, "%f\n", round_gamma(- 11.97523));
  fprintf(stderr, "%f\n", round_gamma(-125.97523));

  return 0;
}

