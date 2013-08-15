
#include <string>
#include <vector>

#include "Point2D.h"

class TSP {
public:
  TSP() 
    : pathLength(0.0)
  {
  }

  void read(std::string const & inputFile);
  void solve();
  void write(std::string const & outputFile) const;

private:
  typedef std::vector<Point2D>   path_type;
  path_type points;

  double pathLength;

  void initialize_order_randomly();
  void initialize_order_greedily();
  void do_simulated_annealing();
  double computePathLength(path_type const & path) const;
  double distance(path_type const & path, size_t idx1, size_t idx2) const;
};
