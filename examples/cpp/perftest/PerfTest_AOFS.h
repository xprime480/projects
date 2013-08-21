#if ! defined(PerfTest_AOFS_h)
#define PerfTest_AOFS_h 1

#include "PerfTest.h"
#include "ThinData.h"

namespace Test {

  class PerfTest_AOFS : public PerfTest
  {
  public:
    PerfTest_AOFS();
  
  private:
    ThinData data[ ARRSIZE ];

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
