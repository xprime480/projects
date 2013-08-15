
#include <iostream>

#include <unordered_set>
#include <cmath>

#include "Point.h"

static size_t const NDIMS = 6;
typedef Point< NDIMS > PointType;

/*!
  \brief type for a poset
*/
typedef std::unordered_set< PointType > Poset;

/*!
  \brief reference a point on the lattice
*/
typedef Poset::const_iterator PosetIter;

int main()
{
  size_t const NDIMS = PointType::NDIMS;
  size_t const MAX_DIM( static_cast< size_t >( std::pow( 1000000.0, 1.0 / NDIMS ) ) );	// range of each dimension [0,MAXDIM)
  size_t const PCT_INSERT( 15 ); // percent of points to create

  std::cout << NDIMS << " dimensions, each from 0 to "
	    << ( MAX_DIM - 1 ) << "\n";
  std::cout  << "###########################\n";

  srand( time( 0 ));

  /*
   */

  Poset poset;

  /*
   * create the poset, inserting points randomly.
   * 
   * The technique here only works if MAX_DIM ^ NDIMS <= the maximum
   * value that a size_t holds.
   */
  PointType point;
  size_t max_idx = 1;
  for ( size_t i = 0 ; i < NDIMS ; ++i ) {
    max_idx *= MAX_DIM;
  }
  for ( size_t idx = 0 ; idx < max_idx ; ++idx ) {
    if ( std::rand() % 100 >= PCT_INSERT ) {
      continue;
    }

    size_t t = idx;
    for ( size_t i = 0 ; i < NDIMS ; ++i ) {
      point.idx[ i ] = t % MAX_DIM;
      t /= MAX_DIM;
    }

    poset.insert( point );
    // std::cout << point << "\n";
  }

  std::cout << poset.size() << " points created\n";
  std::cout  << "###########################\n";
  
  /*
   * find everything that is along an axis from origin;
   * probability that there are none is vanishingly small;
   *
   */
  PosetIter end = poset.end();
  PointType ref = { 0 };		// initialization guarantees all 0

  for ( int idx = 0 ; idx < NDIMS ; ++idx ) {
    for ( int val = ref.idx[ idx ] ; val < MAX_DIM ; ++val ) {
      if ( 0 != idx && 0 == val ) {
	continue;		// only test the origin once.
      }
      PointType p = ref;
      p.idx[ idx ] = val;
      PosetIter pos = poset.find( p );
      if ( end != pos ) {
	std::cout << "matched: " << *pos << "\n";
      }
    }
  }

  std::cout  << "###########################\n";

  /*
   * print all elements > a reference value
   */
  for ( int idx = 0 ; idx < NDIMS ; ++idx ) {
    ref.idx[ idx ] = ( 4 * MAX_DIM ) / 5;
  }
  for ( PosetIter pos = poset.begin() ; pos != end ; ++pos ) {
    if ( ref < *pos ) {
      std::cout << *pos << "\n";
    }
  }

  return 0;
}
