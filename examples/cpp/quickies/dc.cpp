#include <iostream>

struct B {
  int x;
  virtual ~B() {}
};

struct D : public B {
  int y;
};

void f( B & b) {
  D & d = dynamic_cast<D &>(b);
  std::cout << d.y << std::endl;
}

int main(int, char **) 
{
  D d;
  d.x = 1; d.y = 2;
  f(d);
}
