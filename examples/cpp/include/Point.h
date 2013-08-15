#if ! defined( POINT_H )
#define POINT_H

#include <cstdlib>
#include <unordered_set>
#include <sstream>

/*!
  \brief an N dimensional point
*/
template< size_t N >
struct Point
{
  static size_t const NDIMS = N;
  int idx[ N ];
};

namespace std {			// have to define template
				// specialization in original namespace
  /*!
    \brief Overload the hashing function for our key type
  */
  template< size_t N >
  struct hash< Point< N > >
  {
    typedef Point< N > HashedType;
    static size_t const  shift = 8 * sizeof ( int ) / HashedType::NDIMS;
      
    size_t operator()( HashedType const & pt ) const
    {
      size_t result = 0;

      for ( size_t idx = 0 ; idx < HashedType::NDIMS ; ++ idx ) {
	size_t const tmp = static_cast< size_t >( pt.idx[ idx ] );
	result ^= tmp << (shift * idx);
      }
      return result;
    }
  };
}

/*!
  \brief equality operator for Point

  true iff all indices are equal
  
  \param p1 one point
  \param p2 other point
  
  \return equality
*/
template < size_t NDIMS >
bool operator==( Point< NDIMS > const & p1, Point< NDIMS > const & p2 )
{
  for ( size_t idx = 0 ; idx < NDIMS ; ++idx ) {
    if ( p1.idx[ idx ] != p2.idx[ idx ] ) {
      return false;
    }
  }
  return true;
}

/*!
  \brief less than operator for Point

  true iff all indices in the first are < the corresponding index in
  the second
  
  \param p1 one point
  \param p2 other point
  
  \return equality
*/
template< size_t NDIMS >
bool operator<( Point< NDIMS > const & p1, Point< NDIMS > const & p2 )
{
  for ( size_t idx = 0 ; idx < NDIMS ; ++idx ) {
    if ( p1.idx[ idx ] > p2.idx[ idx ] ) {
      return false;
    }
  }
  return ! ( p1 == p2 );
}


/*!
  \brief output a point to a stream
  
  \param os the stream
  \param p the point

  \return the input stream
*/
template< size_t NDIMS >
std::ostream & operator<<( std::ostream & os, Point< NDIMS > const & p ) 
{
  std::stringstream s;
  s << p.idx[ 0 ];
  for ( size_t idx = 1 ; idx < NDIMS ; ++idx ) {
    s << " " << p.idx[ idx ];
  }
  os << s.str();
  return os;
}

#endif
