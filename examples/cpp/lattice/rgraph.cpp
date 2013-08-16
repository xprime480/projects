
#include <iostream>

#include "Graph.h"
#include "GraphPolicies.h"

int main( int argc, char ** argv )
{
  std::srand( time( 0 ) );

  // Graph g(BoundsPolicyQuad1(), AcceptPolicyTree());
  BoundsPolicyCircle bp(10);
  AcceptPolicyTree   ap;
  Graph g(bp, ap);
  int count = 25;
  if ( argc > 1 ) {
    count = std::atoi( argv[1] );
  }
  //g.randomWalk(Point(0, 0), count);
  g.makeRandom(count);
  std::cout << g << std::endl;

  return 0;
}
