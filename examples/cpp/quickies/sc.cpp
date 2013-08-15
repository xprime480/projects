
#include <cstdio>

struct F
{
  char v[4];
};

int main( int, char ** )
{
  F f;
  f.v[0] = 'a';
  f.v[1] = 'b';
  f.v[2] = 'c';
  f.v[3] = 'd';

  for ( int i = 0 ; i < 4 ; ++ i ) {
    unsigned long l = static_cast< unsigned long >( f.v[i] );
    printf( "%lu\n", l );
  }

  return 0;
}
