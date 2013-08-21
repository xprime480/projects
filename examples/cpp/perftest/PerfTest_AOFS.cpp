
#include "PerfTest_AOFS.h"

namespace Test {

  PerfTest_AOFS::PerfTest_AOFS()
    : PerfTest()
  {
  }

  void PerfTest_AOFS::setX(int i, double v)
  {
    data[i].x = v;
  }

  void PerfTest_AOFS::setY(int i, double v)
  {
    data[i].y = v;
  }

  void PerfTest_AOFS::setZ(int i, double v)
  {
    data[i].z = v;
  }

  double PerfTest_AOFS::getX(int i)
  {
    return data[i].x;
  }

  double PerfTest_AOFS::getY(int i)
  {
    return data[i].y;
  }

  double PerfTest_AOFS::getZ(int i)
  {
    return data[i].z;
  }

  char const * PerfTest_AOFS::identify() {
    return "Array of Structs Test";
  }
}

