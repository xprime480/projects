
#include <string>
#include <vector>

#include "Point2D.h"

class TSP {
public:
  void read(std::string const & inputFile);
  void solve();
  void write(std::string const & outputFile) const;

private:
  std::vector<Point2D>   points;
};
