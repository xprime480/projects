#if ! defined(GraphPolicies_h)
#define GraphPolicies_h 1

#include "Point.h"
#include "Edge.h"
#include "Graph.h"

/**
 * This policy ensures that all points are in quadrant 1 of the graph
 */
class BoundsPolicyQuad1 : public BoundsPolicy
{
public:
  virtual bool outOfBounds(Graph const & g, Point const & p) const
  {
    return p.getX() < 0 || p.getY() < 0;
  }
};

/**
 * This policy ensures that all points are in a bounding circle of a
 * defined radius.
 */
class BoundsPolicyCircle : public BoundsPolicy
{
public:
  BoundsPolicyCircle(int r_)
    : r(r_)
  {
  }

  virtual bool outOfBounds(Graph const & g, Point const & p) const
  {
    // stay inside a cirle of a given radius
    int const x = p.getX();
    int const y = p.getY();
    return x*x + y*y > r*r;
  }

private:
  int r;
};

/**
 * This policy accepts transitions that either extend to an unvisited
 * point or traverse an existing edge.  This allows the creation of a
 * tree structure.
 */
class AcceptPolicyTree : public AcceptPolicy
{
public:
  virtual bool accept(Graph const & g, Point const & from, Point const & to) const
  {
    return ( ! g.hasNode(to) ) || g.hasEdge(Edge(from, to));
  }
};

#endif
