#if ! defined(Point_h)
#define Point_h 1

#include <cstdlib>

class Point
{
public:

  Point()
    : x(0)
    , y(0)
  {
  }

  Point(int x_, int y_)
    : x(x_)
    , y(y_)
  {
  }
  
  int getX() const
  {
    return x;
  }

  int getY() const
  {
    return y;
  }

  bool operator==(Point const & p) const
  {
    return p.x == x && p.y == y;
  }

  bool operator<(Point const & p) const
  {
    return x < p.x || ( x == p.x && y < p.y );
  }

  Point randomNeighbor() const
  {
    int i = std::rand() % 4;
    switch ( i ) {
    case 0:
      return north();
    case 1:
      return south();
    case 2:
      return east();
    case 3:
      return west();
    default :
      return north();
    }
  }

  Point north() const
  {
    return Point(x, y+1);
  }

  Point east() const
  {
    return Point(x+1, y);
  }

  Point south() const
  {
    return Point(x, y-1);
  }

  Point west() const
  {
    return Point(x-1, y);
  }

  template < typename T >
  T & display(T & out) const
  {
    out << "(" << x << "," << y << ")";
    return out;
  }

private:
  int x;
  int y;
};

template < typename T >
T & operator<<(T & out, Point const & p)
{
  return p.display(out);
}

#endif

