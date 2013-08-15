
#include <iostream>
#include <vector>
#include <algorithm>

void display( char const * msg, std::vector<int> const & v )
{
  std::cout << msg << ": ";

  for ( int i = 0 ; i < v.size() ; ++i ) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}

int main( int argc, char ** argv )
{
  int vals[] = { 1,3,5,7,2,4,6 };
  std::vector<int> v( vals, vals + sizeof(vals)/sizeof(vals[0]) );
  display("initial", v);

  std::make_heap( v.begin(), v.end() );
  display("heapified", v);

  std::pop_heap( v.begin(), v.end() ); 
  display("pop_heap", v);
  v.pop_back();
  display("pop_back", v);

  v.push_back(16);
  display("push_back", v);
  std::push_heap( v.begin(), v.end() ); 
  display("push_heap", v);

  std::pop_heap( v.begin(), v.end() ); 
  display("pop_heap", v);
  v.pop_back();
  display("pop_back", v);
}
