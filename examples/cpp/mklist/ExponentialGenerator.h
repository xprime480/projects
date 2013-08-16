#if ! defined(ExponentialGenerator_h)
#define ExponentialGenerator_h 1

#include <vector>

#include "Generator.h"

class ExponentialGenerator : public Generator
{
public:
  ExponentialGenerator(int _min, int _max, int _half);
  virtual int gen();

private:
  int min;
  int max;
  int half;

  std::vector<double> cdf;
  void prepareCDF();
};

#endif // not defined ExponentialGenerator_h
