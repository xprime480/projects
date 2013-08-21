
#include "PerfTest_AOFLS.h"

namespace Test {

  PerfTest_AOFLS::PerfTest_AOFLS()
    : PerfTest()
  {
  }

  void PerfTest_AOFLS::setX(int i, double v)
  {
    data[i].x = v;
  }

  void PerfTest_AOFLS::setY(int i, double v)
  {
    data[i].y = v;
  }

  void PerfTest_AOFLS::setZ(int i, double v)
  {
    data[i].z = v;
  }

  double PerfTest_AOFLS::getX(int i)
  {
    return data[i].x;
  }

  double PerfTest_AOFLS::getY(int i)
  {
    return data[i].y;
  }

  double PerfTest_AOFLS::getZ(int i)
  {
    return data[i].z;
  }

  char const * PerfTest_AOFLS::identify() {
    return "Array of Padded Structs Test";
  }
}

