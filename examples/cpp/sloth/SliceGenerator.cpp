
#include <sstream>

#include "Form.h"
#include "FormFactory.h"

#include "SliceGenerator.h"

using namespace std;
using namespace Sloth;

SliceGenerator::SliceGenerator(int _start, int _stop, int _step)
  : start(_start)
  , stop(_stop)
  , step(_step)
{
}

bool SliceGenerator::isNil() const
{
  return start >= stop;
}

Form SliceGenerator::head() const
{
  if ( isNil() ) {
    return headFromNil();
  }

  return FormFactory::makeInt(start);
}

Form SliceGenerator::tail() const
{
  if ( isNil() ) {
    return FormFactory::makeNil();
  }

  SliceGenerator * gen = new SliceGenerator(start+step, stop, step);
  return FormFactory::makeSequence(gen);
}

string SliceGenerator::toString() const
{
  stringstream s;
  s << "(slice " << start << ":" << stop << ":" << step << ")";
  return s.str();
}
