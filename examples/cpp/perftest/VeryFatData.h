#if ! defined(VeryFatData_h)
#define VeryFatData_h 1

namespace Test {
  struct VeryFatData
  {
    int    key1;
    int    key2;
    char   buffer[140];
    int    key3;
    double x;
    double fill1;
    double y;
    double fill2;
    bool   someFlag;
    double z;

    static char const * identify()
    {
      return "VeryFatData";
    }

  };


}

#endif
