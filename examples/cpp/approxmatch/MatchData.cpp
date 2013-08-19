
#include <iostream>

#include "MatchData.h"

using namespace std;

PartialMatchData::PartialMatchData(size_t _score, 
				   size_t _pos,
				   bool   _inTranspose,
				   char   _transposeChar)
  : score(_score)
  , pos(_pos)
  , inTranspose(_inTranspose)
  , transposeChar(_transposeChar)
{
}


ostream & operator<<(ostream & os, MatchData const & m)
{
  os << m.key << " " << m.value << " [err=" << m.score << "]";
  return os;
}
