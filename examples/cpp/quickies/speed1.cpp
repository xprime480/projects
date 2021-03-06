
#include <vector>
#include <iostream>

size_t const DATA_COUNT_MAX = 100000;
typedef std::vector<double> DataType;

void init( DataType & data )
{
  for ( size_t i = 0 ; i < DATA_COUNT_MAX ; ++i ) {
    data[ i ] = i;
  }
}

double compute( DataType & data ) 
{
  double sum( 0 );
  for ( size_t i = 0 ; i < DATA_COUNT_MAX ; ++i ) {
    sum += data[ i ];
  }
  return sum;
}

int main( int argc, char ** argv )
{
  DataType data;
  data.reserve( DATA_COUNT_MAX );

  init( data );
  std::cerr << compute( data ) << "\n";
}
