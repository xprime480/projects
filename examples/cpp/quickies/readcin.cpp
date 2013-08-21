
#include <iostream>
#include <string>

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


