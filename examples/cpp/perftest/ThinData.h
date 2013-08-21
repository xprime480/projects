#if ! defined(ThinData_h)
#define ThinData_h 1

namespace Test {
  struct ThinData
  {
    double x;
    double y;
    double z;

    static char const * identify()
    {
      return "ThinData";
    }

  };

}

#endif
