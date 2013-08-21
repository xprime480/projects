
#include <sstream>

#include "Form.h"
#include "FormFactory.h"

#include "ListGenerator.h"

using namespace std;
using namespace Sloth;

ListGenerator::ListGenerator(vector<Form> const & _forms)
  : forms(_forms)
{
}

bool ListGenerator::isNil() const
{
  return forms.empty();
}

Form ListGenerator::head() const
{
  if ( isNil() ) {
    return headFromNil();
  }

  return forms.at(0);
}

Form ListGenerator::tail() const
{
  if ( isNil() || forms.size() == 1 ) {
    return FormFactory::makeNil();
  }

  vector<Form> fprime(forms);
  fprime.erase(fprime.begin());
  return FormFactory::makeSequence(new ListGenerator(fprime));
}

string ListGenerator::toString() const
{
  stringstream s;
  s << "[";
  vector<Form>::const_iterator iter = forms.begin();
  vector<Form>::const_iterator end  = forms.end();
  if ( iter != forms.end() ) {
    s << iter->toString();
    ++iter;
  }
  for ( ; iter != forms.end() ; ++iter ) {
    s << " " << iter->toString();
  }
  s << "]";
  return s.str();
}
