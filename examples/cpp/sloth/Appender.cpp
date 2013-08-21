#include <sstream>
#include <string>

#include "Form.h"
#include "FormFactory.h"

#include "Appender.h"

using namespace std;
using namespace Sloth;

Appender::Appender(Form const & _f1, Form const & _f2)
  : f1(_f1)
  , f2(_f2)
{
}

bool Appender::isNil() const
{
  return f1.isNil() && f2.isNil();
}

Form Appender::head() const
{
  if ( isNil() ) {
    return headFromNil();
  }

  if ( f1.isNil() ) {
    return f2.getHead();
  }

  return f1.getHead();
}

Form Appender::tail() const
{
  if ( isNil() ) {
    return FormFactory::makeNil();
  }

  if ( f1.isNil() ) {
    return f2.getTail();
  }

  return FormFactory::makeSequence(new Appender(f1.getTail(), f2));
}

string Appender::toString() const
{
  static string const prefix = "(append ";
  static string const sep    = " ";
  static string const suffix = ")";

#if 0
  string output;
  output = prefix + f1.toString() + sep + f2.toString() + suffix;
  return output;
#endif

  stringstream s;
  s << prefix << f1.toString() << sep << f2.toString() << suffix;
  return s.str();
}
