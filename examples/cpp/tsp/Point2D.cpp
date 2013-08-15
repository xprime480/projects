
#include "Point2D.h"

bool Point2D::makePoint(Point2D & point)
{
  point.x = point.y = 0;
  return true;
}

bool Point2D::makePoint(Point2D & point, std::ifstream & pointSource)
{
  if ( ! pointSource ) {
    return false;
  }

  int _x, _y;
  pointSource >> _x >> _y;
  point.x = _x;
  point.y = _y;

  return (bool) pointSource;
}

void Point2D::writePoint(Point2D const & point, 
			 std::ofstream & pointDestination)
{
  pointDestination << point.x << " " << point.y << std::endl;
}

