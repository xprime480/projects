
#include <sstream>

#include "CountGenerator.h"

using namespace std;
using namespace Sloth;

CountGenerator::CountGenerator(Form const & _form)
  : form(_form)
  , count(0)
  , evaled(false)
{
}

int CountGenerator::value() const
{
  if ( evaled ) {
    return count;
  }

  Form f = form;

  while ( f.isSequence() && ! f.isNil() ) {
    count++;
    f = f.getTail();
  }

  evaled = true;
  return count;
}

string CountGenerator::toString() const
{
  stringstream s;
  s << "(count " << form.toString() << ")";
  return s.str();
}
