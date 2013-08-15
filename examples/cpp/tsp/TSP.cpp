
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

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
}

void TSP::solve()
{
  // initialize_order_randomly();
  initialize_order_greedily();
  pathLength = computePathLength(points);

  do_simulated_annealing();
}

void TSP::write(std::string const & outputFile) const
{
  ofstream pointDestination(outputFile.c_str());

  std::vector<Point2D>::const_iterator b;
  std::vector<Point2D>::const_iterator e = points.end();
  for ( b = points.begin() ; b != e ; ++b ) {
    Point2D::writePoint(*b, pointDestination);
  }

  pointDestination << endl << endl;
  pointDestination << "Path Length = " << pathLength << endl;

}

void TSP::initialize_order_randomly()
{
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(points.begin(), points.end(), default_random_engine(seed));
}

void TSP::initialize_order_greedily()
{
  for ( size_t idx1 = 0 ; idx1 < points.size() ; ++idx1 ) {
    double base_distance = distance(points, idx1, idx1+1);
    for ( size_t idx2 = idx1+2 ; idx2 < points.size() ; ++idx2 ) {
      double new_distance = distance(points, idx1, idx2);
      if ( new_distance < base_distance ) {
	base_distance = new_distance;
	swap(points[idx1+1], points[idx2]);
      }
    }
  }
}

template <typename T>
void make_indexes(size_t & idx1, size_t & idx2, size_t max, T & gen)
{
  for ( ;; ) {
    idx1 = gen();
    idx2 = gen();

    if ( idx1 == idx2 ) {
      continue;
    }
    if ( idx1 > idx2 && (idx1-idx2) > max ) {
      continue;
    }
    if ( (idx2-idx1) > max ) {
      continue;
    }

    return;
  }
}

void TSP::do_simulated_annealing()
{
  default_random_engine generator;
  uniform_int_distribution<size_t> distribution(0,points.size()-1);
  auto indexer = bind ( distribution, generator );

  for ( size_t max_step_size = points.size() / 2
	  ; max_step_size > 0
	  ; --max_step_size ) {
    for ( size_t count = 0 ; count < 100 ; ++count ) {
      
      size_t idx1, idx2;
      make_indexes(idx1, idx2, max_step_size, indexer);
      path_type temp_points = points;
      swap(temp_points[idx1], temp_points[idx2]);
      double temp_length = computePathLength(temp_points);
      if ( temp_length < pathLength ) {
	points = temp_points;
	pathLength = temp_length;
      }
    }
  }
}



double TSP::computePathLength(std::vector<Point2D> const & path) const
{
  if ( path.size() < 2 ) {
    return 0.0;
  }

  double len = distance(path, 0, path.size() - 1);
  for ( size_t i = 0 ; i < path.size() - 1 ; ++i ) {
    len += distance(path, i, i+1);
  }
  return len;
}

double TSP::distance(path_type const & path, size_t idx1, size_t idx2) const
{
  Point2D const & p1 = path[idx1];
  Point2D const & p2 = path[idx2];

  double dx = p1.x - p2.x;
  double dy = p1.y - p2.y;

  return sqrt(dx * dx + dy * dy);
}

