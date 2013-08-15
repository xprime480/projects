
#include <iostream>
#include <vector>
#include <algorithm>

struct XYZ {
  int x,y,z;
};

template < typename T >
class VofT {
public:

  VofT( int count )
    : data( count, T() )
  {
  }

  void add( T & item )
  {
    data.push_back( item );
  }

  template < typename F >
  void apply( F const & f )
  {
    std::for_each(data.begin(), data.end(), f);
  }

private:
  std::vector< T > data;
  
};

class Initer {
public:
  template < typename T >
  int operator()( T & t ) {
    t.x = 10*i + 7;
    t.y = 7*i  + 10;
    ++i;
  }

private:
  static int i;
};

int Initer::i = 0;

class Adder {
public:
  template < typename T >
  int operator()( T & t ) {
    return t.z = t.x + t.y;
  }
};

class Shower {
public:
  template < typename T >
  void operator()( T & t ) {
    std::cout << t.x << " + " << t.y << " = " << t.z << std::endl;
  }
};


void runtest()
{
  VofT< XYZ > v(10);
  
  v.apply( Initer() );
  v.apply( Adder() );
  v.apply( Shower() );
}


int main( int argc, char ** argv )
{
  runtest();
  return 0;
}
