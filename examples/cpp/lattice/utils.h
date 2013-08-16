#if ! defined(utils_h)
#define utils_h 1

#include <cmath>
#include <set>

#include "Point.h"

template < typename T, typename U >
T & operator<<(T & out, std::set< U > const & s)
{
  typename std::set<U>::const_iterator iter;
  for ( iter = s.begin() ; iter != s.end() ; ++iter ) {
    out << *iter << " ";
  }

  return out;
}

double distance(Point const & p1, Point const & p2)
{
  int dx = p1.getX() - p2.getX();
  int dy = p1.getY() - p2.getY();
  return std::sqrt(dx * dx + dy * dy);
}

#endif
