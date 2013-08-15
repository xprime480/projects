#include <tr1/memory>
#include <iostream>

class X 
{
public:
  X( int x_ ) : x( x_ ) {}
  ~X() { std::cout << "deleting " << x << "\n"; }
  void f() const { std::cout << "accessing " << x << "\n"; }
private:
  int x; 
};

typedef std::tr1::shared_ptr< X > sharedX;

void fx( sharedX const & sx )
{
  sx->f();
}

int main( int, char** )
{
  sharedX sx1( new X( 3 ) );
  sharedX sx2( sx1 );

  fx( sx1 );
  fx( sx2 );
}
