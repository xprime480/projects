
#include <string>
#include <iostream>
#include <memory>

//
// Not compilable
//

struct BargyBase
{
  virtual void call() = 0;
};

template < typename T >
struct Bargy : public BargyBase
{
  Bargy( T o )
    : op( o )
  {
  }

  virtual void call()
  {
    op();
  }

private:
  T op;
};

template < typename T >
Bargy < T > * make_bargy( T const & t )
{
  return new Bargy< T >( t );
}

template < typename T >
Bargy < T > * make_bargy( Bargy < T > * t ) 
{
  return new Bargy< T >( *t );
}


class Argy
{
public:
  template < typename T >
  Argy( char const * n, T t ) 
    : name( n )
    , sb( make_bargy( t ) ) 
  {
  }

  Argy( Argy const & a )
    : name ( a.name ) 
    , sb ( make_bargy( a.sb.get() ) )
  {
  }

  void operator()()
  {
    std::cout << name << ": ";
    sb->call();
  }

private:
  std::string const name;
  std::auto_ptr<BargyBase> sb;

  Argy & operator=( Argy const & );
};

void somefunc()
{
  std::cout << "Somefunc\n";
}

template < typename T >
struct Functor
{
  Functor( T t )
    : val( t )
  {
  }

  void operator()()
  {
    std::cout << val << "\n";
  }
private:
  T val;
};

int main( int argc, char ** argv )
{
  Argy    a1( "a1", somefunc );
  Argy    a2( "a2", Functor< double >( 3.33 ) );
  Argy    a3( "a3", Functor< std::string >( "The rain in spain" ) );
  Argy    a4 = a3;

  a1();
  a2();
  a3();
  a4();
}

