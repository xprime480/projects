
//
// No longer in TR1 if you compile with -std=c++11
// 
#include <functional>
#include <utility>

#include <iostream>
#include <vector>
#include <cassert>

int add(int x, int y) { return x+y; }
bool adjacent(int x, int y) { return x == y-1 || x == y+1; }

struct compare_and_record {
  std::vector< std::pair< int, int > > values;

  bool operator()( int x, int y )
  {
    values.push_back( std::make_pair( x, y ) );
    return x == y;
  }
};

int tres( int a, int b, int c ) { return a > b ? b : c; }
 
int main( int, char ** )
{   
  std::function< int ( int, int ) > f;
    
  f = &add; 
  std::cout << f( 2, 3 ) << std::endl; // 5
    
  f = std::minus< int >();
  std::cout << f( 2, 3 ) << std::endl; // -1

  assert( f );		      // okay, f refers to a minus<int> object
    
  std::function< bool ( int, int ) > g;
  assert( !g );			// okay, g doesn't refer to any object
    
  g = &adjacent;
  assert( g( 2, 3 ));		// okay, adjacent(2, 3) returns true
    
  g = std::equal_to< long >();	// argument conversions ok
  assert( g( 3, 3 ) );	   //okay, equal_to<long>()(3, 3) returns true

  compare_and_record car;
  g = std::ref( car );

  assert( g( 3, 3 ) );		// okay, and adds (3, 3) to car.values

  g = f;	 // okay, int return value of f is convertible to bool

  std::function< int ( int, int, int ) > h;
  h = &tres;

  std::cout << h( 5, 5, 1033 ) << std::endl;
}
