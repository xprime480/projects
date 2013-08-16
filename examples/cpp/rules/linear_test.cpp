
#include "Linear.h"
#include "Hasse.h"

int main( int argc, char ** argv )
{
  Linear          linear( 3, 10 );
  Hasse< Linear > hasse( linear );
}
