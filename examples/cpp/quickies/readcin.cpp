
#include <iostream>
#include <string>

/*
 * This example shows how to read from a generic stream.
 *
 * In this case, the stream is built from std::cin.  The input is just
 * echoed to the output (std::cout).
 */

void f( std::istream & is ) 
{
  char buf[ 128 ];
  std::streamsize c;

  for ( ;; ) {
    is.read( buf, sizeof ( buf ) - 1 );
    c = is.gcount();
    if ( ! c ) 
      break;
    buf[ c ] = '\0';
    std::cout << buf;
  }
}

int main( int, char ** )
{
  f( std::cin );
  return 0;
}


