#include <iostream>


template < typename T1 = char *, 
	   typename T2 = char * >
struct X
{
  static void f( T1 const & t1 = md< T1 >(), 
		 T2 const & t2 = md< T2 >() )
  {
    if ( &t1 != &md< T1 >() ) {
      std::cerr << t1;
    }
    if ( &t2 != &md< T2 >() ) {
      std::cerr << t2;
    }
    std::cerr << "\n";
  }

private:
  template< typename T >
  static T const & md()
  {
    static T t;
    return t;
  }

  
};

void x()
{
  X<>::f();
}

template < typename T1 >
void x( T1 const & t1 )
{
  X< T1 >::f( t1 );
}

template < typename T1, typename T2 >
void x( T1 const & t1, T2 const & t2 )
{
  X< T1, T2 >::f( t1, t2 );
}

int main( int argc, char ** argv )
{
  x();
  x( 2 );
  x( "cat: ", 18 );
  return 0;
}
