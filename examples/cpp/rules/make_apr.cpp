
#include <iostream>

#include "Hasse.h"
#include "PosetItems_2D.h"

int main( int argc, char ** argv )
{
  srand( time( 0 ) );
  if ( argc > 1 ) {
    if ( std::string( "-r" ) == argv[ 1 ] ) {
      if ( argc > 2 ) {
	int i = atoi( argv[ 2 ] );
	PosetItems_2D_Random t( i );
      }
      else {
	std::cerr << "-r requires a numeric argument\n";
	return 1;
      }
    }
    else {
      PosetItems_2D_File t( argv[ 1 ] );
    }
  }
  else {
    PosetItems_2D_Random t( 20 );
  }

  return 0;
}

