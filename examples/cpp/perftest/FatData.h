#if ! defined(FatData_h)
#define FatData_h 1

namespace Test {
  struct FatData
  {
    int    key1;
    int    key2;
    int    key3;
    double x;
    double fill1;
    double y;
    double fill2;
    bool   someFlag;
    double z;

    static char const * identify()
    {
      return "FatData";
    }

  };


}

#endif
