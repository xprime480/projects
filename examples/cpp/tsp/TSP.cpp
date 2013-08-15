
#include <fstream>
#include <iostream>

#include "TSP.h"

using namespace std;

void TSP::read(std::string const & inputFile)
{
  ifstream pointSource(inputFile.c_str());

  size_t count = 0;

  for ( ;; ) {
    Point2D next;
    if ( Point2D::makePoint(next, pointSource) ) {
      points.push_back(next);
      ++count;
    }
    else {
      break;
    }
  }

  std::cout << count << " points read." << std::endl;
}

void TSP::solve()
{
}

void TSP::write(std::string const & outputFile) const
{
  ofstream pointSource(outputFile.c_str());
}
