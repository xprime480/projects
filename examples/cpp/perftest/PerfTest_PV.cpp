
#include "PerfTest_PV.h"

namespace Test {

  PerfTest_PV::PerfTest_PV()
    : PerfTest()
  {
    x.reserve( ARRSIZE );
    y.reserve( ARRSIZE );
    z.reserve( ARRSIZE );
  }

  void PerfTest_PV::setX(int i, double v)
  {
    x[i] = v;
  }

  void PerfTest_PV::setY(int i, double v)
  {
    y[i] = v;
  }

  void PerfTest_PV::setZ(int i, double v)
  {
    z[i] = v;
  }

  double PerfTest_PV::getX(int i)
  {
    return x[i];
  }

  double PerfTest_PV::getY(int i)
  {
    return y[i];
  }

  double PerfTest_PV::getZ(int i)
  {
    return z[i];
  }

  char const * PerfTest_PV::identify() {
    return "Parallel Vector Test";
  }
}

