
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

template <typename T>
void display( char const * msg, T const & v )
{
  std::cout << msg << ": ";

  for ( size_t i = 0 ; i < v.size() ; ++i ) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}

void vector_heap()
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

  std::greater<int> gt;
  std::make_heap( v.begin(), v.end(), gt );
  display("heapified - greater", v);

  v.push_back(16);
  std::make_heap( v.begin(), v.end(), gt );
  display("push_back 16 - greater", v);

  v.push_back(0);
  std::make_heap( v.begin(), v.end(), gt );
  display("push_back 0 - greater", v);
}

void array_heap()
{
    std::array<int, 10> a = { 0, 1, 2, 3, 4 };
    size_t last = 5;
    display("init", a);

    std::make_heap( a.begin(), a.begin() + last );
    display("heapified", a);

    std::pop_heap( a.begin(), a.begin() + last );
    --last;
    display("pop", a);

    a[last++] = 33;
    std::push_heap( a.begin(), a.begin() + last );
    display("push", a);

}

int main( int argc, char ** argv )
{
    // vector_heap();
    array_heap();
}
