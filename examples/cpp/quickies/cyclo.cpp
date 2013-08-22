/*
 * compute the cyclomatic number of a graph
 */

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

/*
 * Graphs are specified by adding vertices and edges.
 *
 */
class Graph
{
private:
  struct Edge
  {
    Edge()
    {
      init();
    }

    void init()
    {
      ends[0] = ends[1] = 0;
      flags = 0;
    }

    int      ends[2];
    unsigned flags;

    enum { in_use = 0x1 };
  };

public:

  Graph()
    : edges( 0 )
    , len( 0 )
    , analyzed( false )
  {
    initMemory( 16 );
  }

  ~Graph()
  {
    free( edges );
  }

  void read( char const * fname )
  {
    std::ifstream in( fname );
    if ( ! in ) {
      std::cerr << "error opening filename " << fname << "\n";
      return;
    }
    int x;
    int y;
    int e(0);
    while ( true ) {
      in >> x >> y;
      if ( in.eof() ) {
	break;
      }
      ++e;
      addEdge( x, y );
    }

    std::cerr << e << " edge" << (e == 1 ? "" : "s") << " read\n";
  }

  void addVertex( int i )
  {
  }

  void addEdge( int i, int j )
  {
    if ( i == j ) {
      std::cerr << "warning: self-edges not supported\n";
      return;
    }
    if ( i > j ) {
      std::swap( i, j );
    }

    size_t p = 0;
    for ( ; p < len ; ++p ) {
      if ( edges[p].ends[0] == i && edges[p].ends[1] == j ) {
	std::cerr << "warning: multigraphs not supported\n";
	return;
      }
    }

    appendEdge( i, j, p );
  }

  int cyclomaticNumber()
  {
    analyze();
    return 0;
  }

private:

  Edge * edges;
  size_t len;
  bool   analyzed;

  void initMemory( size_t newLen )
  {
    size_t oldLen( len );
    len = newLen;

    edges = (Edge *) realloc( edges, len * sizeof ( Edge ) );
    if ( ! edges ) {
      std::cerr << "No memory\n";
      throw 2;
    }

    for ( size_t i = oldLen ; i < len ; ++i ) {
      edges[ i ].init();
    }
  }

  void appendEdge( int i, int j, size_t p )
  {
    analyzed = false;
    if ( len == p ) {
      initMemory( 2 * len );
    }

    edges[ p ].ends[ 0 ] = i;
    edges[ p ].ends[ 1 ] = j;
    edges[ p ].flags    |= Edge::in_use;
  }

  void analyze()
  {
    analyzed = true;
  }

};

int main( int argc, char ** argv )
{
  Graph g;
  if ( argc > 1 ) {
    g.read( argv[ 1 ] );
  }
  else {
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,1);
  }
  std::cerr << "Cyclomatic number is: " << g.cyclomaticNumber() << "\n";
}


