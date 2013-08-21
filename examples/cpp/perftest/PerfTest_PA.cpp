
#include "PerfTest_PA.h"

namespace Test {

  PerfTest_PA::PerfTest_PA()
    : PerfTest()
  {
  }

  void PerfTest_PA::setX(int i, double v)
  {
    x[i] = v;
  }

  void PerfTest_PA::setY(int i, double v)
  {
    y[i] = v;
  }

  void PerfTest_PA::setZ(int i, double v)
  {
    z[i] = v;
  }

  double PerfTest_PA::getX(int i)
  {
    return x[i];
  }

  double PerfTest_PA::getY(int i)
  {
    return y[i];
  }

  double PerfTest_PA::getZ(int i)
  {
    return z[i];
  }

  char const * PerfTest_PA::identify() {
    return "Parallel Array Test";
  }
}

