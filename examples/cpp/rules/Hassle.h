#if ! defined( Hasse_h )
#define Hasse_h 1

#include <cstdlib>
#include <deque>
#include <iostream>
#include <set>
#include <unordered_set>

#include "PosetItems.h"


template < typename T  >
class Hasse
{
private:
  typedef T                                   PosetItems;
  typedef typename PosetItems::PosetItemType  ItemType;
  typedef std::unordered_set< ItemType >      PosetData;
  typedef typename PosetData::const_iterator  PosetIter;
  typedef std::deque< ItemType >              PointQueue;

  struct GraphNode;

  class GraphTable
  {
  public:
    GraphTable()
      : count( 0 )
      , max( 4 )
    {
      init( 0 );
    }

    GraphTable( GraphTable const & that )
    {
      copy( that );
    }

    GraphTable & operator=( GraphTable const & that )
    {
      copy( that );
      return *this;
    }

    ~GraphTable()
    {
      if ( nodes ) {
	std::free( nodes );
	nodes = 0;
	count = 0;
	max = 4;
      }
    }

    size_t size() const
    {
      return count;
    }

    GraphNode * operator[]( size_t n )
    {
      if ( n < 0 || n >= count ) {
	throw "GraphNode: index out of range";
      }
      return nodes[ n ];
    }

    GraphNode const * operator[]( size_t n ) const
    {
      if ( n < 0 || n >= count ) {
	throw "GraphNode: index out of range";
      }
      return nodes[ n ];
    }

    GraphNode ** begin()
    {
      return nodes;
    }

    GraphNode ** end()
    {
      return nodes + count;
    }

    GraphNode * const * begin() const
    {
      return nodes;
    }

    GraphNode * const * end() const
    {
      return nodes + count;
    }

    void clear()
    {
      init( 0 );
    }

    void insert( GraphNode * n )
    {
      if ( count >= max ) {
	max *= 2;
	init( count );
      }
      nodes[ count++ ] = n;
    }

    template < typename U >
    void insert( U from, U to ) 
    {
      while ( from != to ) {
	insert( *from );
	++from;
      }
    }

  private:
    size_t       count;
    size_t       max;
    GraphNode ** nodes;

    void init( size_t c )
    {
      count = c;
      size_t size = max * sizeof( GraphNode * );
      if ( nodes ) {
	nodes = (GraphNode **) std::realloc( (void *) nodes, size );
      }
      else {
	nodes = (GraphNode **) std::malloc( size );
      }
      if ( 0 == nodes ) {
	throw "GraphTable: out of memory";
      }

      for ( size_t i = count ; i < max ; ++i ) {
	nodes[ i ] = 0;
      }
    }

    void copy( GraphTable const & that )
    {
      if ( this == &that ) {
	return;
      }

      max = that.max;
      init( that.count );
      for ( size_t i = 0 ; i < count ; ++i ) {
	nodes[ i ] = that.nodes[ i ];
      }
    }

  };
  
  struct GraphNode
  {
    ItemType    item;
    GraphTable  successors;
  };

public:

  Hasse( PosetItems & pi )
    : items( pi )
  {
    GraphNode origin;
    GraphNode infinity;
    origin.item   = items.origin();
    infinity.item = items.infinity();
    
    // append( origin, infinity );

    while ( items.hasMore() ) {

      GraphNode * n = new GraphNode;
      n->item = items.next();
      append( origin, *n );
      
    }

    for ( size_t i = 0 ; i < origin.successors.size() ; ++ i ) {
      print_graph( *origin.successors[ i ] );
    }

    // print_all( poset );
    // find_rules(); 
  }

private:
  PosetItems & items;
  PosetData poset;
  PointQueue processing;

  void add( ItemType const & p ) 
  {
    PosetIter pos = poset.find( p );
    if ( poset.end() == pos ) {
      poset.insert( p );
      processing.push_back( p );
    }
  }

  /*!
    \brief print a poset
    
    \param ps the data
  */
  void print_all( PosetData const & ps ) const
  {
    PosetIter end = ps.end();
    for ( PosetIter pos = ps.begin() ; pos != end ; ++pos ) {
      items.point( *pos );
    }
  }

  void find_rules() 
  {
    while ( ! processing.empty() ) {
      ItemType origin = processing.front();
      processing.pop_front();

      PosetData candidates;
      find_greater( candidates, poset, origin );

      PointQueue temp;
      std::copy( candidates.begin(), candidates.end(), 
		 std::back_inserter( temp ) );
      while ( ! temp.empty() ) {
	ItemType o2 = temp.front();
	temp.pop_front();
	PosetIter pos = candidates.find( o2 );
	if ( candidates.end() != pos ) {
	  PosetData not_nbrs;
	  find_greater( not_nbrs, poset, o2 );
	  
	  PosetData c2;
	  find_difference( c2, candidates, not_nbrs );
	  candidates = c2;
	}
      }

      PosetIter cend = candidates.end();
      for ( PosetIter cpos = candidates.begin() ; cend != cpos ; ++cpos ) {
	items.edge( origin, *cpos );
      }
    }
  }

  void append( GraphNode & from, GraphNode & to )
  {
    if ( to.item < from.item ) {
      append( to, from );
      return;
    }

    if ( ! (from.item < to.item) ) {
      return;
    }

    GraphTable inner;
    GraphTable outer;
    
    get_inner_frontier( from, to, inner );

    get_outer_frontier( from, to, outer );
    compress_outer_frontier( outer );

    add_to_inner( inner, to );
    add_outer( outer, to );

    remove_redundant( inner, to.successors );
  }

  void print_g( GraphTable const & g ) 
  {
    for ( size_t i = 0 ; i < g.size() ; ++i ) {
      GraphNode const & succ = *g[ i ];
      items.point( succ.item );
    }
  }

  void get_inner_frontier( GraphNode & from, 
			   GraphNode & to, 
			   GraphTable & frontier )
  {
    if ( ! ( from.item < to.item ) ) {
      return;
    }

    GraphTable & g = from.successors;
    for ( size_t i = 0 ; i < g.size() ; ++i ) {
      GraphNode & succ = *g[ i ];
      if ( to.item < succ.item ) {
	GraphTable t;
	get_inner_frontier( succ, to, t );
	std::set< GraphNode * > n;
	std::copy( t.begin(), t.end(), std::inserter( n, n.end() ) );
	std::copy( frontier.begin(), frontier.end(), 
		   std::inserter( n, n.end() ) );
	frontier.clear();
	frontier.insert( n.begin(), n.end() );
      }
    }
    if ( 0 == frontier.size() ) {
      frontier.insert( &from );
    }
  }

  void get_outer_frontier( GraphNode & from, 
			   GraphNode & to, 
			   GraphTable & frontier )
  {
    if ( to.item < from.item ) {
      frontier.insert( &from );
      return;
    }

    GraphTable t = from.successors;
    for ( size_t i = 0 ; i < t.size() ; ++i ) {
      GraphNode & succ = *t[ i ];
      get_outer_frontier( succ, to, frontier );
    }
  }

  void compress_outer_frontier( GraphTable & outer )
  {
    GraphTable temp;


    size_t end = outer.size();
    for ( size_t p1 = 0 ; p1 < end ; ++p1 ) {
      bool add( true );
      GraphNode & smaller = *outer[ p1 ];
      for ( size_t p2 = 0 ; p2 < end ; ++p2 ) {
	GraphNode & larger = *outer[ p2 ];
	if ( larger.item < smaller.item ) {
	  add = false;
	  break;
	}
      }
      if ( add ) {
	temp.insert( outer[ p1 ] );
      }
    }

    outer = temp;
  }

  void add_to_inner( GraphTable & inner, GraphNode & to )
  {
    for ( size_t i = 0 ; i < inner.size() ; ++i ) {
      inner[ i ]->successors.insert( &to );
    }
  }

  void add_outer( GraphTable & outer, GraphNode & to ) 
  {
    GraphTable & ts = to.successors;
    for ( size_t i = 0 ; i < outer.size() ; ++i ) {
      ts.insert( outer[ i ] );
    }
  }

  void remove_redundant( GraphTable & inner, GraphTable & trans )
  {
    typedef std::set< GraphNode * > GNS;
	
    for ( int i = 0 ; i < inner.size() ; ++i ) {
      GNS gns;
      GraphTable & is = inner[ i ]->successors;
      std::set_difference( is.begin(), is.end(),
			   trans.begin(), trans.end(),
			   std::inserter( gns, gns.begin() ) );
      is.clear();
      is.insert( gns.begin(), gns.end() );
    }
  }

  void print_graph( GraphNode const & g )
  {
    GraphTable gs = g.successors;
    for ( size_t i = 0 ; i < gs.size() ; ++i ) {
      GraphNode const & succ = *gs[ i ];
      bool print = true;
      if ( ! ( g.item == items.origin() ) &&
	   ! ( succ.item == items.origin() ) &&
	   ! ( g.item == items.infinity() ) &&
	   ! ( succ.item == items.infinity() ) ) {
	items.edge( g.item, succ.item );    
      }
      print_graph( succ );
    }
  }

  /*!
    \brief find all points which are greater than a given point
    
    \param dest where to put the results
    \param src where to look
    \param min the starting point
  */
  void find_greater( PosetData & dest, 
		     PosetData const & src, 
		     ItemType const & min ) const
  {
    PosetIter end = src.end();
    for ( PosetIter pos = src.begin() ; pos != end ; ++pos ) {
      if ( items.less( min, *pos ) ) {
	dest.insert( *pos );
      }
    }
  }

  /*!
    \brief find all points which are in left but not right
    
    \param dest where to put the results
    \param left starting set
    \param right set to subtract out
  */
  void find_difference( PosetData & dest, 
			PosetData const & left, 
			PosetData const & right )
  {
    PosetIter lend = left.end();
    PosetIter rend = right.end();
    for ( PosetIter lpos = left.begin() ; lpos != lend ; ++lpos ) {
      PosetIter rpos = right.find( *lpos );
      if ( right.end() == rpos ) {
	dest.insert( *lpos );
      }
    }
  }
};

#endif
