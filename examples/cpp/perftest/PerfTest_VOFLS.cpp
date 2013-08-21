
#include "PerfTest_VOFLS.h"

namespace Test {

  PerfTest_VOFLS::PerfTest_VOFLS()
    : PerfTest()
  {
    data.reserve( ARRSIZE );
  }

  void PerfTest_VOFLS::setX(int i, double v)
  {
    data[i].x = v;
  }

  void PerfTest_VOFLS::setY(int i, double v)
  {
    data[i].y = v;
  }

  void PerfTest_VOFLS::setZ(int i, double v)
  {
    data[i].z = v;
  }

  double PerfTest_VOFLS::getX(int i)
  {
    return data[i].x;
  }

  double PerfTest_VOFLS::getY(int i)
  {
    return data[i].y;
  }

  double PerfTest_VOFLS::getZ(int i)
  {
    return data[i].z;
  }

  char const * PerfTest_VOFLS::identify() {
    return "Vector of Padded Structs Test";
  }
}

