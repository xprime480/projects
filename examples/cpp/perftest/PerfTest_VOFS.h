#if ! defined(PerfTest_VOFS_h)
#define PerfTest_VOFS_h 1

#include <vector>

#include "PerfTest.h"
#include "ThinData.h"

namespace Test {

  class PerfTest_VOFS : public PerfTest
  {
  public:
    PerfTest_VOFS();
  
  private:
    std::vector<ThinData> data;

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
