#if ! defined(PerfTest_VOS_h)
#define PerfTest_VOS_h 1

#include <sstream>
#include <vector>

#include "PerfTest.h"


namespace Test {

  template< typename DataT >
  class PerfTest_VOS : public PerfTest
  {
  public:
    PerfTest_VOS() 
      : PerfTest()
    {
      data.reserve(ARRSIZE);
    }

  private:
    std::vector<DataT> data;

    void setX(int i, double v)
    {
      data[i].x = v;
    }

    void setY(int i, double v)
    {
      data[i].y = v;
    }

    void setZ(int i, double v)
    {
      data[i].z = v;
    }

    double getX(int i)
    {
      return data[i].x;
    }

    double getY(int i)
    {
      return data[i].y;
    }

    double getZ(int i)
    {
      return data[i].z;
    }

    char const * identify()
    {
      static bool done = false;
      static std::stringstream s;
      if ( ! done ) {
	s << "Vector of " << DataT::identify() << " Test";
	done = true;
      }
      return s.str().c_str();
    }
  };

}

#endif
