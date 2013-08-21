
#include <sstream>

#include "Form.h"
#include "FormFactory.h"

#include "SingletonGenerator.h"

using namespace std;
using namespace Sloth;

SingletonGenerator::SingletonGenerator(int _value)
  : value(_value)
{
}

bool SingletonGenerator::isNil() const
{
  return false;
}

Form SingletonGenerator::head() const
{
  return FormFactory::makeInt(value);
}

Form SingletonGenerator::tail() const
{
  return FormFactory::makeNil();
}

string SingletonGenerator::toString() const
{
  stringstream s;
  s << "(" << value << ")";
  return s.str();
}
