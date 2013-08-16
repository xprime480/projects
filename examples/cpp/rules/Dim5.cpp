
#include <iostream>

#include "PosetItems.h"
#include "Dim5.h"

Dim5::Dim5( size_t c, int m )
  : max_count( c )
  , current( 0 )
  , max_val( m )
{
  // srand( time( 0 ) );
  srand( max_count * 1000 + max_val );
}
  
bool Dim5::hasMore() const
{
  return current < max_count;
}

Dim5::PosetItemType Dim5::next()
{
  if ( hasMore() ) {
    ++current;
  }
  PosetItemType item;
  for ( size_t i = 0 ; i < 5 ; ++i ) {
    item.idx[ i ] = 1 + rand() % max_val;
  }
  return item;
}

Dim5::PosetItemType Dim5::origin() const
{
  PosetItemType item;
  std::fill( item.idx, item.idx + 5, 0 );
  return item;
}

Dim5::PosetItemType Dim5::infinity() const
{
  PosetItemType item;
  std::fill( item.idx, item.idx + 5, max_val + 1 );
  return item;
}

void Dim5::point( PosetItemType const & a )
{
  std::cout << "point at " << a << "\n";
}

void Dim5::edge( PosetItemType const & a, PosetItemType const & b )
{
  std::cout << "edge from " << a << " to " << b << "\n";
}
