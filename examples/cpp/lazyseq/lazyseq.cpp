
#include <iostream>
#include <sstream>
#include <fstream>

#include "AnonSeq.h"
#include "AnonSeqBase.h"
#include "Fibonacci.h"
#include "Hamming.h"
#include "LazyForm.h"
#include "LazyInterp.h"
#include "LazySeq.h"
#include "LazySeqUtils.h"
#include "List.h"
#include "Naturals.h"

using namespace std;

namespace {
  
  void count(LazySeq<int> * s)
  {
    cout << "Count = " << LazySeqUtils<int>::count(s) << endl;
  }

  void printN(LazySeq<int> * s, size_t n)
  {
    LazySeq<int> * z = LazySeqUtils<int>::take(s, n);
    LazySeqStat::addref(z);
    LazySeqUtils<int>::print(z);
    LazySeqStat::deref(z);
  }

  void dolazy(char const * spec)
  {
    using namespace lazy;
    LazyInterp interp;
    LazyForm * form = interp.parse(spec);
    form->print();
  }

  void test(size_t depth)
  {
    if ( depth == 0 ) {
      return;
    }

    LazySeq<int> * seq = new AnonSeqBase<int>();
    TRACEALLOC(seq);
    LazySeqStat::addref(seq);
    for ( size_t i = 1 ; i < depth ; ++i ) {
      LazySeq<int> * temp = new AnonSeq<int>(seq);
      TRACEALLOC(temp);
      LazySeqStat::addref(temp);
      LazySeqStat::deref(seq);
      seq = temp;
    }

    // cout << "Length is " << LazySeqUtils::count(seq) << endl;
    LazySeq<int> * minmax = LazySeqUtils<int>::minmax(seq);
    LazySeqStat::addref(minmax);
    cout << "Extremes: ";
    printN(minmax, 2);
    LazySeqStat::deref(minmax);

    LazySeqStat::deref(seq);
  }

  template <typename T>
  class StackStacker
  {
  public:
    StackStacker(T & loc, T const & value)
      : location(loc)
      , oldvalue(loc)
    {
      location = value;
    }

    ~StackStacker()
    {
      location = oldvalue;
    }

  private:
    T & location;
    T const oldvalue;
  
  };
}

int main(int argc, char ** argv)
{

  if ( false ) {
    for ( size_t i = 1 ; i <= 25 ; ++i ) {
      test(i);			// 
    }
    LazySeqStat::report();
  }

  if ( argc > 1 ) {
    ifstream lines(argv[1]);
    char command[2000] ;
    if ( ! lines ) {
      cerr << "Error opening command file " << argv[1] << endl;
    }
    while ( lines.good() ) {
      lines.getline(command, 2000);
      dolazy(command);
      // LazySeqStat::report(); 
    }
  }

  return 0;
}
