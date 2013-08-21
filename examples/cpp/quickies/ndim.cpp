
#include <map>
#include <cmath>
#include <iostream>
#include <sstream>
#include <cstdlib>

struct Key_3D
{
  int key[ 3 ];
};

bool operator<( Key_3D const & k1, Key_3D const & k2 )
{
  return ( k1.key[ 0 ] < k2.key[ 0 ] &&
	   k1.key[ 1 ] < k2.key[ 1 ] &&
	   k1.key[ 2 ] < k2.key[ 2 ] );
}

std::ostream & operator<<( std::ostream & os, Key_3D const & key ) 
{
  std::stringstream s;
  s << "{" << key.key[ 0 ]
    << "," << key.key[ 1 ]
    << "," << key.key[ 2 ]
    << "}";
  os << s.str();
  return os;
}

typedef std::map< Key_3D, int > PointVal;
typedef PointVal::const_iterator Iter;

int main()
{
  PointVal  vals;
  size_t const MAX_POINT( 1000 );
  size_t const MAX_DIM( 50 );

  for ( size_t i = 0 ; i < MAX_POINT ; ++i ) {
    Key_3D key;
    key.key[ 0 ] = rand() % MAX_DIM;
    key.key[ 1 ] = rand() % MAX_DIM;
    key.key[ 2 ] = rand() % MAX_DIM;
    vals[ key ] = int(i);
    std::cout << i << ": " << key << "\n";
  }

  std::cout << "++++++++++++++++++++++++++++++++++++++\n";

  Iter end = vals.end();
  for ( Iter pos = vals.begin() ; pos != end ; ++pos ) {
    std::cout << pos->first << " " << pos->second << "\n";
  }
  
}
