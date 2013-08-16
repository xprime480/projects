
#include "Dim5.h"
#include "Hasse.h"

int main( int argc, char ** argv )
{
  try {
    Dim5          dim5( 3000, 10 );
    Hasse< Dim5 > hasse( dim5 );
  }
  catch ( char * m ) {
    std::cout << "exception: " << m << "\n";
    return 1;
  }
  catch ( ... ) {
    return 1;
  }
  
  return 0;
}
