
#include <fstream>

struct Point2D {
  int x;
  int y;
  
  static bool makePoint(Point2D & point);
  static bool makePoint(Point2D & point, std::ifstream & pointSource);

  static void writePoint(Point2D const & point, 
			 std::ofstream & pointDestination);

};
