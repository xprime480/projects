
#include <iostream>
#include <set>
#include <cstdlib>

#include "Tester.h"

Tester::Tester(int size)
  : max(size)
{
  std::fill_n(std::back_inserter(counts), size, Collector());
}

void Tester::run(int tries)
{
  for ( int i = 0 ; i < tries ; ++i ) {
    runonce();
  }
}

void Tester::report() const
{
  std::cout << "Tester for " << max << " items" << std::endl;
  
  for ( int i = 0 ; i < max ; ++i ) {
    Collector const & c = counts[i];
    std::cout << "--- for " << (i+1) << " items ---" << std::endl;
    c.report();
    std::cout << "--------------------------" << std::endl;
  }
	  
}

void Tester::runonce()
{
  int pass = 0;

  seen.clear();

  for ( int i = 0 ; i < max ; ++i ) {
    while ( seen.size() <= i ) {
      ++pass;
      int n = std::rand() % max;
      seen.insert(n);
    }

    counts[i].add(pass);
  }
}
