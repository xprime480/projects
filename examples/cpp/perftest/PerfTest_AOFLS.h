#if ! defined(PerfTest_AOFLS_h)
#define PerfTest_AOFLS_h 1

#include "PerfTest.h"
#include "FatData.h"

namespace Test {

  class PerfTest_AOFLS : public PerfTest
  {
  public:
    PerfTest_AOFLS();
  
  private:
    FatData data[ ARRSIZE ];

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
