
#include <sstream>

#include "FormFactory.h"

#include "Infinite.h"

using namespace std;
using namespace Sloth;

Infinite::Infinite(Form const & _v)
  : value(_v)
{
}

bool Infinite::isNil() const
{
  return false;
}

Form Infinite::head() const
{
  return value;
}

Form Infinite::tail() const
{
  return FormFactory::makeSequence(new Infinite(value));
}

string Infinite::toString() const
{
  stringstream s;
  s << "[infinite: " << value.toString() << "]";
  return s.str();
}
