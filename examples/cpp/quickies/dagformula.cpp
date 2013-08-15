
#include <iostream>
#include <iterator>

unsigned long long pascal[11][11];

void do_pascal()
{
  for ( int n = 0 ; n < 11 ; ++n ) {
    pascal[n][0] = 1;
    int k;
    for ( k = 1 ; k <= n ; ++k ) {
      pascal[n][k] = pascal[n-1][k-1] + pascal[n-1][k];
    }
    for ( k = n+1 ; k < 11 ; ++k ) {
      pascal[n][k] = 0;
    }
  }
}

int main(int argc, char ** argv) 
{
  do_pascal();

  unsigned long long dag[11];
  unsigned long long o = 1;

  dag[0] = 1;

  for ( int n = 1 ; n < 11 ; ++n ) {
    dag[n] = 0;
    int i = -1;
    for ( int k = 1 ; k <= n ; ++k ) {
      i *= -1;
      dag[n] += i * pascal[n][k] * (o << (k * (n-k))) * dag[n-k];
    }
  }

  std::copy(dag, dag+11, std::ostream_iterator<long long>(std::cout, ", "));
  std::cout << std::endl;

  return 0;
}
