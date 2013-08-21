
#include "PerfTest_VOFS.h"

namespace Test {

  PerfTest_VOFS::PerfTest_VOFS()
    : PerfTest()
  {
    data.reserve( ARRSIZE );
  }

  void PerfTest_VOFS::setX(int i, double v)
  {
    data[i].x = v;
  }

  void PerfTest_VOFS::setY(int i, double v)
  {
    data[i].y = v;
  }

  void PerfTest_VOFS::setZ(int i, double v)
  {
    data[i].z = v;
  }

  double PerfTest_VOFS::getX(int i)
  {
    return data[i].x;
  }

  double PerfTest_VOFS::getY(int i)
  {
    return data[i].y;
  }

  double PerfTest_VOFS::getZ(int i)
  {
    return data[i].z;
  }

  char const * PerfTest_VOFS::identify() {
    return "Vector of Structs Test";
  }
}

