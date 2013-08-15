

#include <iostream>

template < typename T > class Y;

template < typename T > 
class X 
{
public:
  
  friend class Y< T >;
  
  X( T v )
    : q( v )
  {
  }
private:
  T q;
};

template < typename T >
class Y
{
public:
  void f( X< T > & x)
  {
    std::cerr << x.q << "\n";
  }
};

int main( int, char ** )
{
  X< int >  xi( 30 );
  Y< int >  yi;
  X < double > xd( 234.3 );

  yi.f( xi );
  // yi.f( xd );  /* this line won't compile */

  return 0;
}


