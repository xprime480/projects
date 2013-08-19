#include <algorithm>

#include "Score.h"

using namespace std;

Score::Score(size_t _s, size_t _t, size_t v)
  : valid(true)
  , s(_s)
  , t(_t)
  , score(v)
{
}

Score::Score(Score const & _s)
{
  *this = _s;
}

Score & Score::operator=(Score const & _s)
{
  valid = _s.valid;
  s     = _s.s;
  t     = _s.t;
  score = _s.score;
  return *this;
}

size_t Score::getOffset1() const 
{
  return s;
}

size_t Score::getOffset2() const 
{
  return t;
}

size_t Score::getScore() const
{
  return score;
}

void Score::advance(size_t sc, size_t ss, size_t st)
{
  score += sc;
  s     += ss;
  t     += st;
}

bool Score::isValid() const
{
  return valid;
}

void Score::invalidate()
{
  valid = false;
}


bool Score::operator<(Score const & s2) const
{
  Score const & s1 = *this;

  if ( s1.valid != s2.valid ) {
    return s1.valid;		// sort invalid scores to the end;
  }

  if ( s1.score < s2.score ) {
    return true;
  }
  if ( s2.score < s1.score ) {
    return false;
  }

  size_t off11 = s1.getOffset1();
  size_t off12 = s1.getOffset2();
  size_t off21 = s2.getOffset1();
  size_t off22 = s2.getOffset2();

  size_t max1 = max(off11, off12);
  size_t max2 = max(off21, off22);
  if ( max1 < max2 ) {
    return false;
  }
  if ( max2 < max1 ) {
    return true;
  }

  size_t l1 = off11 + off12;
  size_t l2 = off21 + off22;
  if ( l1 < l2 ) {
    return false;
  }
  if ( l2 < l1 ) {
    return true;
  }

  if ( off11 < off21 ) {
    return true;
  }
  if ( off21 < off11 ) {
    return false;
  }

  return off12 < off22;
}
