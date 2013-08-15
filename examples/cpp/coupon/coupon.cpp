
#include <iostream>

#include "Collector.h"
#include "Tester.h"

void simple_test() 
{
  Collector c;

  c.add(2);
  c.add(3);
  c.add(-1);

  c.report();
}

void runtest(int min, int max)
{
  for ( int i = min ; i <= max ; ++i ) {
    Tester t(i);
    t.run(1000);
    t.report();
    std::cout << "==========================" << std::endl;
  }
}

int main( int argc, char ** argv )
{
  simple_test();
  std::cout << "**************************" << std::endl;
  runtest(1, 30);
  std::cout << "**************************" << std::endl;
  return 0;
}
