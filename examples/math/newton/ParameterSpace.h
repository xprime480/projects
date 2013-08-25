#if ! defined( ParameterSpace_h ) 
#define ParameterSpace_h 1

#include <vector>

struct ParameterSpace
{
public:
  ParameterSpace( size_t n )
    : size( n )
  {
    data.reserve( n );
  }

  double operator[]( size_t idx ) const
  {
    if ( idx > size ) {
      throw "Bounds Exception";
    }
    return data[ idx ];
  }

  double & operator[]( size_t idx )
  {
    if ( idx > size ) {
      throw "Bounds Exception";
    }
    return data[ idx ];
  }

private:
  std::vector< double > data;
  size_t                size;
};

#endif
