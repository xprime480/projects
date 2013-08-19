
#include <cstring>
#include <stdexcept>

#include "ForwardStrPointer.h"

using namespace std;

ForwardStrPointer::ForwardStrPointer(char const * s)
  : pch(s)
  , len(strlen(s))
{
}

size_t ForwardStrPointer::getLen() const 
{
  return len;
} 

char ForwardStrPointer::getCh(size_t offset) const
{
  if ( offset < getLen() ) {
    return pch[offset];
  }
  throw runtime_error("ForwardStrPointer::getCh: offset out of bounds");
}

void ForwardStrPointer::advance(size_t n)
{
  if ( n > getLen() ) {
    throw runtime_error("ForwardStrPointer::advance: offset out of bounds");
  }

  pch += n;
  len -= n;
}
