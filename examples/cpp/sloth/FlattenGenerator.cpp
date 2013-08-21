#include <sstream>

#include "Form.h"
#include "FormFactory.h"
#include "ListGenerator.h"

#include "FlattenGenerator.h"

using namespace std;
using namespace Sloth;

FlattenGenerator::FlattenGenerator(Form const & _form)
  : form(_form)
  , evaled(false)
  , flattened(FormFactory::makeNil())
{
}

bool FlattenGenerator::isNil() const
{
  if ( form.isNil() ) {
    return true;
  }
  
  if ( ! evaled ) {
    evaled = true;
    vector<Form> forms;
    helper(form, forms);
    flattened = FormFactory::makeSequence(new ListGenerator(forms));
  }

  return flattened.isNil();
}

Form FlattenGenerator::head() const
{
  if ( isNil() ) {
    return headFromNil();
  }

  return flattened.getHead();
}

Form FlattenGenerator::tail() const
{
  if ( isNil() ) {
    return FormFactory::makeNil();
  }

  return flattened.getTail();
}

string FlattenGenerator::toString() const
{
  stringstream s;
  s << "(flatten " << form.toString() << ")";
  return s.str();
}


void FlattenGenerator::helper(Form const & f, std::vector<Form> & forms) const
{
  if ( ! f.isSequence() ) {
    forms.push_back(f);
    return;
  }

  if ( f.isNil() ) {
    return;
  }

  helper(f.getHead(), forms);
  helper(f.getTail(), forms);
}
