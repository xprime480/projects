
#include <string>
#include <iostream>
#include <memory>

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


  void operator()()
  {
    std::cout << name << ": ";
    sb->call();
  }

private:
  std::string const name;
  std::shared_ptr<BargyBase> sb;
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

template <typename T>
Functor<T> make_functor(T const & value) 
{
  return Functor<T>(value);
}

int main( int argc, char ** argv )
{
  double      a2Val(3.33);
  std::string a3Val("The rain in spain");

  Argy    a1( "a1", somefunc );
  Argy    a2( "a2", make_functor( a2Val ) );
  Argy    a3( "a3", make_functor( a3Val ) );
  Argy    a4 = a3;

  a1();
  a2();
  a3();
  a4();
}

