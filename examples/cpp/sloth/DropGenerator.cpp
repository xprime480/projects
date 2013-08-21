
#include <sstream>

#include "Form.h"
#include "FormFactory.h"

#include "DropGenerator.h"

using namespace std;
using namespace Sloth;

DropGenerator::DropGenerator(Form const & _form, int _count)
  : form(_form)
  , count(_count)
  , evaled(false)
{
}

bool DropGenerator::isNil() const
{
  if ( ! evaled ) {
    eval();
  }

  return form.isNil();
}

Form DropGenerator::head() const
{
  if ( isNil() ) {
    return headFromNil();
  }

  return form.getHead();
}

Form DropGenerator::tail() const
{
  if ( isNil() ) {
    return FormFactory::makeNil();
  }

  return form.getTail();
}

string DropGenerator::toString() const
{
  stringstream s;
  s << "(drop " << count << " " << form.toString() << ")";
  return s.str();
}

void DropGenerator::eval() const
{
  while ( count > 0 ) {
    if ( form.isNil() ) {
      count = 0;
      break;
    }

    form = form.getTail();
    --count;
  }

  evaled = true;
}
