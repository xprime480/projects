#if ! defined(PerfTest_PV_h)
#define PerfTest_PV_h 1

#include <vector>

#include "PerfTest.h"

namespace Test {

  class PerfTest_PV : public PerfTest
  {
  public:
    PerfTest_PV();
  
  private:
    std::vector< double > x;
    std::vector< double > y;
    std::vector< double > z;

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
