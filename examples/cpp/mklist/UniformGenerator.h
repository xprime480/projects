#if ! defined(UniformGenerator_h)
#define UniformGenerator_h 1

#include "Generator.h"

class UniformGenerator : public Generator
{
public:
  UniformGenerator(int _min, int _max);
  virtual int gen();

private:
  int min;
  int max;
};

#endif // not defined UniformGenerator_h
