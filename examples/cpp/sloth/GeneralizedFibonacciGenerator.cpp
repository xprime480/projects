
#include <limits>
#include <sstream>

#include "Form.h"
#include "FormFactory.h"

#include "GeneralizedFibonacciGenerator.h" 

using namespace std;
using namespace Sloth;

GeneralizedFibonacciGenerator::GeneralizedFibonacciGenerator(int _a, int _b)
  : a(_a)
  , b(_b)
{
}

bool GeneralizedFibonacciGenerator::isNil() const
{
  return a < 0;
}

Form GeneralizedFibonacciGenerator::head() const
{
  if ( isNil() ) {
    return headFromNil();
  }

  return FormFactory::makeInt(a);
}

Form GeneralizedFibonacciGenerator::tail() const
{
  if ( isNil() || (numeric_limits<int>::max() - b) < a) {
    return FormFactory::makeNil();
  }

  GeneralizedFibonacciGenerator * gen =
    new GeneralizedFibonacciGenerator(b, a+b);
  return FormFactory::makeSequence(gen);
}

string GeneralizedFibonacciGenerator::toString() const
{
  stringstream s;
  s << "(gfibonacci " << a << " " << b << ")";
  return s.str();
}

