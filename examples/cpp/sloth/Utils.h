#if ! defined(Utils_h)
#define Utils_h 1

namespace Sloth
{
  template <typename T>
  void deleter(void * p)
  {
    T * t = (T*) p;
    delete t;
  }
}

#endif // not defined Utils_h
