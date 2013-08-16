
#include <cstdlib>

#include "UniformGenerator.h"

using namespace std;

UniformGenerator::UniformGenerator(int _min, int _max)
  : min(_min)
  , max(_max)
{
}

int UniformGenerator::gen()
{
  return min + rand() % (max - min);
}

