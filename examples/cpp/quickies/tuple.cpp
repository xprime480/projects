#include <tuple>
#include <iostream>

typedef std::tuple< int, char const ** > Arg_t;
typedef std::tuple< int, int, int > I3_t;

char const * arg[] = { "one", "two", 0 };

int main( int, char** )
{
  //Arg_t   a = std::make_tuple( 3, arg );
  I3_t  i3a = std::make_tuple( 42, 17, 99 );
  I3_t  i3b = std::make_tuple( 42, 23, 99 );

  std::cout << std::get<2>(i3a) << "\n";
  std::cout << ( i3a < i3b ) << "\n";
}

