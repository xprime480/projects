#if ! defined(Edge_h)
#define Edge_h 1

#include <set>
#include <numeric>

#include "Point.h"

class Edge
{
public:
  Edge(Point const & p1_, Point const & p2_)
    : p1(std::min(p1_, p2_))
    , p2(std::max(p1_, p2_))
  {
  }

  bool operator==(Edge const & e) const
  {
    return e.p1 == p1 && e.p2 == p2;
  }

  bool operator<(Edge const & e) const
  {
    return p1 < e.p1 || ( p1 == e.p1 && p2 < e.p2 );
  }

  template < typename T >
  T & display(T & out) const
  {
    out << "[" << p1 << " ... " << p2 << "]";
    return out;
  }

private:
  Point p1;
  Point p2;
  
};

template < typename T >
T & operator<<(T & out, Edge const & e)
{
  return e.display(out);
}

#endif
