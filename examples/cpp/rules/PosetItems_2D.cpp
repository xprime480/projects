
#include <iostream>

#include "PosetItems_2D.h"

void PosetItems_2D::point( PosetItemType const & a )
{
}

void PosetItems_2D::edge( PosetItemType const & a, PosetItemType const & b )
{
}

PosetItems_2D_Random::PosetItems_2D_Random( size_t count, size_t max )
{
}
  
bool PosetItems_2D_Random::hasMore() const
{
  return false;
}

PosetItems_2D_Random::PosetItemType PosetItems_2D_Random::next()
{
  return PosetItems_2D_Random::PosetItemType();
}


PosetItems_2D_Random::PosetItemType PosetItems_2D_Random::origin() const
{
  throw "PosetItems_2D_Random::origin unimplemented";
  PosetItemType item;
  return item;
}

PosetItems_2D_Random::PosetItemType PosetItems_2D_Random::infinity() const
{
  throw "PosetItems_2D_Random::infinity unimplemented";
  PosetItemType item;
  return item;
}


PosetItems_2D_File::PosetItems_2D_File( char const * data_file )
  : filled( false )
{
}
  
bool PosetItems_2D_File::hasMore() const
{
  return false;
}

PosetItems_2D_File::PosetItemType PosetItems_2D_File::next()
{
  return PosetItems_2D_File::PosetItemType();
}

PosetItems_2D_File::PosetItemType PosetItems_2D_File::origin() const
{
  throw "PosetItems_2D_File::origin unimplemented";
  PosetItemType item;
  return item;
}

PosetItems_2D_File::PosetItemType PosetItems_2D_File::infinity() const
{
  throw "PosetItems_2D_File::infinity unimplemented";
  PosetItemType item;
  return item;
}
