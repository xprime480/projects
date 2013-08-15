#include <iostream>

void test(bool a, bool b, bool c)
{
  bool d =  a && b  || c;
  bool e = (a && b) || c;
  bool f = a && (b || c);
  

  std::cout << a << b << c << " " << d << e << f << std::endl;
}


int main(int argc, char ** argv) 
{
  test(false, false, false);
  test(false, false,  true);
  test(false,  true, false);
  test(false,  true,  true);
  test( true, false, false);
  test( true, false,  true);
  test( true,  true, false);
  test( true,  true,  true);
}
