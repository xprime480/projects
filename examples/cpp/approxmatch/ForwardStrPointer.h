#if ! defined(ForwardStrPointer_h)
#define ForwardStrPointer_h 1

#include <cstdlib>

class ForwardStrPointer
{
public:
  ForwardStrPointer(char const * s);

  size_t getLen() const ;
 
  char getCh(size_t offset) const;

  void advance(size_t n);

private:

  char const * pch;
  size_t len;
};

#endif // not defined ForwardStrPointer_h
