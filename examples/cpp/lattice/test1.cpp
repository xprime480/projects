
#include <iostream>
#include <set>

#include "Point.h"
#include "Edge.h"
#include "Graph.h"
#include "GraphPolicies.h"

#include "utils.h"

int main( int argc, char ** argv )
{
  Point p1(2,4);
  Point p2(3,4);
  Point p3(2,3);
  Edge e1(p1, p2);
  Edge e2(p2, p3);
  Edge e3(p1, p3);

  std::set<Point> sp;
  sp.insert(p1);
  sp.insert(p2);
  sp.insert(p3);

  std::set<Edge> se;
  se.insert(e1);
  se.insert(e2);
  se.insert(e3);
  
  std::cout << sp << std::endl;
  std::cout << se << std::endl;

  std::cout << p2 << std::endl;
  std::cout << e3 << std::endl;
  p1.display(std::cout);
  e1.display(std::cout); 
  std::cout << std::endl;

  BoundsPolicyQuad1 bp;
  AcceptPolicyTree  ap;
  Graph g(bp, ap);
  g.makeRandom(3);
  std::cout << g << std::endl;
}


