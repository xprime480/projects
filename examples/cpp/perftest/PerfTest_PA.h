#if ! defined(PerfTest_PA_h)
#define PerfTest_PA_h 1

#include "PerfTest.h"

namespace Test {

  class PerfTest_PA : public PerfTest
  {
  public:
    PerfTest_PA();
  
  private:
    double x[ ARRSIZE ];
    double y[ ARRSIZE ];
    double z[ ARRSIZE ];

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
