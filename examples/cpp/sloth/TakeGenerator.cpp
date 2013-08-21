
#include <sstream>

#include "Form.h"
#include "FormFactory.h"

#include "TakeGenerator.h"

using namespace std;
using namespace Sloth;

TakeGenerator::TakeGenerator(Form const & _form, int _count)
  : form(_form)
  , count(_count)
{
}

bool TakeGenerator::isNil() const
{
  if ( count <= 0 ) {
    return true;
  }

  return form.isNil();
}

Form TakeGenerator::head() const
{
  if ( isNil() ) {
    return headFromNil();
  }

  return form.getHead();
}

Form TakeGenerator::tail() const
{
  if ( isNil() ) {
    return FormFactory::makeNil();
  }

  TakeGenerator * gen = new TakeGenerator(form.getTail(), count - 1);
  return FormFactory::makeSequence(gen);
}

string TakeGenerator::toString() const
{
  stringstream s;
  s << "(take " << count << " " << form << ")";
  return s.str();
}
