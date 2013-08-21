#if ! defined(PerfTest_VOFLS_h)
#define PerfTest_VOFLS_h 1

#include <vector>

#include "FatData.h"
#include "PerfTest.h"

namespace Test {

  class PerfTest_VOFLS : public PerfTest
  {
  public:
    PerfTest_VOFLS();
  
  private:
    std::vector< FatData > data;

    void setX(int i, double v);
    void setY(int i, double v);
    void setZ(int i, double v);
    double getX(int i);
    double getY(int i);
    double getZ(int i);

    char const * identify();
  };

}

#endif
