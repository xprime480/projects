
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>

#include "PerfTest.h"

namespace Test {

  PerfTest::PerfTest()
  {
    initRNG();
  }

  PerfTest::~PerfTest()
  {
  }

  int PerfTest::run(int argc, char ** argv)
  {
    int count( 100 );
    if ( argc > 1 ) {
      count = std::atoi( argv[ 1 ] );
    }

    time_t start = time(0);

    for ( int i = 0 ; i < count ; ++i ) {
      populate();
      compute();
      report();
    }

    time_t end = time(0);
    std::cout << "ran " << this->identify() << " in " << (end-start) << " seconds" << std::endl;

    return 0;
  }

  void PerfTest::initRNG()
  {
    static bool init( false );
    if ( ! init ) {
      srand( time( 0 ) );
      init = true;
    }
  }


  void PerfTest::populate()
  {
    for ( size_t i = 0 ; i < ARRSIZE ; ++i ) {
      setX(i, 1000 * ( ((double) rand()) / RAND_MAX ));
      setY(i,    5 * ( ((double) rand()) / RAND_MAX ));
    }
  }

  void PerfTest::compute()
  {
    for ( size_t i = 0 ; i < ARRSIZE ; ++i ) {
      setZ(i, (getX(i) * std::exp( getY( i ) )));
    }
  }

  void PerfTest::report()
  {
    double max = getZ( 0 );
    for ( size_t i = 1 ; i < ARRSIZE ; ++i ) {
      max = std::max( max, getZ( i ) );
    }
    std::cerr << "Max = " << max << "\n";
  }

}
