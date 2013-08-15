
#include <iostream>
#include <set>

template < typename T >
class H
{
private:
  typedef T              P;
  typedef typename P::I  I;

  struct G;

  typedef G *                PG;
  typedef std::set< void * > S;

  struct G
  {
    I    i;
    S    s;
  };

  G root;

public:
  H()
  {
    root.i = T::root();
  }

  void add( size_t c )
  {
    for ( size_t n = 0 ; n < c ; ++n ) {
      PG item = new G;
      item->i = T::next();
      root.s.insert( item );
    }
  }

  void print()
  {
    print( root );
  }

  /*
   * problematic function
   */
  void print( G const & item )
  {
    typedef S::const_iterator SCI; // problem <why?>
    SCI end = item.s.end();
    for ( SCI pos = item.s.begin() ; pos != end ; ++pos ) {
      G const & s = *(PG)(*pos);
      std::cout << item.i << " # " << s.i << "\n";
      print( s );
    }
  }

};

class Q
{
public:
  typedef int I;

  static I root()
  {
    return 0;
  }

  static I next()
  {
    static I v = 0;
    return ++v;
  }
};


int main( int argc, char ** argv )
{
  H< Q >   hq;

  hq.add( 5 );
  hq.print();
}


