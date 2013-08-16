#include <iostream>

#include "Graph.h"

int main(int argc, char ** argv)
{
  BoundsPolicy bp;
  AcceptPolicy ap;
  Graph g(bp, ap);
  g.randomWalk(Point(0,0), 5);
  std::cout << g << std::endl;
  return 0;
}
