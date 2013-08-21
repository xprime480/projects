#if ! defined(PerfTest_AOS_h)
#define PerfTest_AOS_h 1

#include <sstream>

#include "PerfTest.h"


namespace Test {

  template< typename DataT >
  class PerfTest_AOS : public PerfTest
  {
  public:
    PerfTest_AOS() 
      : PerfTest()
    {
    }
  
  private:
    DataT data[ ARRSIZE ];

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
	s << "Array of " << DataT::identify() << " Test";
	done = true;
      }
      return s.str().c_str();
    }
  };

}

#endif
