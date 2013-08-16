#if ! defined(Graph_h)
#define Graph_h 1

#include <iostream>
#include <set>
#include <algorithm>

#include "Point.h"
#include "Edge.h"
#include "utils.h"

class Graph;

class BoundsPolicy
{
public:
  virtual bool outOfBounds(Graph const & g, Point const & p) const
  {
    return false;
  }
};

class AcceptPolicy
{
public:
  virtual bool accept(Graph const & g, Point const & from, Point const & to) const
  {
    return true;
  }
};

class Graph 
{
public:
  Graph(BoundsPolicy & bounds_, AcceptPolicy & accept_)
    : bounds(bounds_)
    , accept(accept_)
  {
  }

  void randomWalk(Point const & start, unsigned steps)
  {
    Point p = start;
    nodes.insert( p );

    std::cout << p << std::endl;
    for ( unsigned i = 0 ; i < steps ; ++i ) {
      p = nextPoint( p );
      std::cout << p << std::endl;
    }
  }

  void makeRandom(unsigned count)
  {
    Point p;
    nodes.insert(p);
    while ( nodes.size() < count ) {
      p = nextPoint( p );
    }
  }

  template < typename T >
  T & display(T & out) const
  {
    out << "Nodes: " << std::endl;
    out << nodes     << std::endl;
    out << "Edges: " << std::endl;
    out << edges     << std::endl;
    return out;
  }

  bool hasNode(Point const & p) const
  {
    return nodes.end() != std::find(nodes.begin(), nodes.end(), p);
  }

  bool hasEdge(Edge const & e) const
  {
    return edges.end() != std::find(edges.begin(), edges.end(), e);
  }

private:
  Point nextPoint( Point const & from ) 
  {
    int const TRIES = 30;	// this value gives less than 2 in
				// 10,000 chance of random failure if
				// a path exists.
    Point to = from;
    int i;
    for ( i = 0 ; i < TRIES ; ++i ) {
      to = from.randomNeighbor();
      if ( ! bounds.outOfBounds(*this, to) && accept.accept(*this, from, to) ) {
	edge_type edge(from, to);
	edges.insert(edge);

	nodes.insert(to);

	return to;
      }
    }

    throw "Too many tries failed to create a point";
  }

  BoundsPolicy & bounds;
  AcceptPolicy & accept;

  typedef Point node_type;
  typedef Edge  edge_type;
  std::set< node_type > nodes;
  std::set< edge_type > edges;
};

template < typename T >
T & operator<<(T & out, Graph const & g)
{
  return g.display(out);
}

#endif
