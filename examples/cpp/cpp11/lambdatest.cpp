
#include <iostream>
#include <string>

template <typename T>
void f0(T t)
{
  std::cout << t(0) << std::endl;
}

void lambdatest(int argc, char ** argv)
{
  std::cout << std::boolalpha;

  auto f = [] (int x) { return x+1; };
  auto g = [] (int x) { return x>0 ? "pass" : "fail"; };
  auto h = [] (int x) { return x>0; };
  f0(f);
  f0(g);
  f0(h);
}
