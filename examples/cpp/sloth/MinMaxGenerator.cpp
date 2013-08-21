#include <sstream>

#include "Form.h"
#include "FormFactory.h"
#include "SingletonGenerator.h"

#include "MinMaxGenerator.h"

using namespace std;
using namespace Sloth;

MinMaxGenerator::MinMaxGenerator(Form const & _form)
  : form(_form)
  , evaled(false)
{
}

bool MinMaxGenerator::isNil() const
{
  if ( ! evaled ) {
    empty = form.isNil();
  }

  return empty;
}

Form MinMaxGenerator::head() const
{
  if ( isNil() ) {
    return headFromNil();
  }

  if ( ! evaled ) {
    evaled = true;

    Form f = form;
    Form h = f.getHead();
    f = f.getTail();
    min = max = h.getIntValue();
    
    while ( ! f.isNil() ) {
      h = f.getHead();
      f = f.getTail();

      int v = h.getIntValue();
      if ( v < min ) {
	min = v;
      }
      else if ( v > max ) {
	max = v;
      }
    }
  }

  return FormFactory::makeInt(min);
}

Form MinMaxGenerator::tail() const
{
  if ( isNil() ) {
    return FormFactory::makeNil();
  }

  return FormFactory::makeSequence(new SingletonGenerator(max));
}

string MinMaxGenerator::toString() const
{
  stringstream s;
  s << "(minmax " << form.toString() << ")";
  return s.str();
}
