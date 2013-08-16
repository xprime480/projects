
#include <cstdlib>
#include <iostream>

#include "PosetItems.h"
#include "Linear.h"

Linear::Linear( size_t c, int m )
  : max_count( c )
  , current( 0 )
  , max_val( m )
{
  srand( time( 0 ) );
}
  
bool Linear::hasMore() const
{
  return current < max_count;
}

Linear::PosetItemType Linear::next()
{
  if ( hasMore() ) {
    ++current;
  }
  PosetItemType item = 1 + rand() % max_val;
  return item;
}

Linear::PosetItemType Linear::origin() const
{
  PosetItemType item = 0;
  return item;
}

Linear::PosetItemType Linear::infinity() const
{
  PosetItemType item = 1 + max_val;
  return item;
}

void Linear::point( PosetItemType const & a )
{
  std::cout << "point: " << a << "\n";
}

void Linear::edge( PosetItemType const & a, PosetItemType const & b )
{
  std::cout << "edge from " << a << " to " << b << "\n";
}
