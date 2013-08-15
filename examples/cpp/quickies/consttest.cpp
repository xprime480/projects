
#include <iostream>
#include <list>


struct X 
{
  std::list<int> ys;
  int x;
};

void exec(std::list<X> const & xs) 
{
  std::list<X>::const_iterator iter;
  for ( iter = xs.begin() ; iter != xs.end() ; ++iter ) {
    iter->ys.push_back(iter->ys.size());
  }
}

int main(int argc, char ** argv)
{
  std::list<X> xs;
  for ( int i = 0 ; i < 5 ; ++i ) {
    X x;
    x.x = i;
    xs.push_back(x);
  }

  exec(xs);
}
