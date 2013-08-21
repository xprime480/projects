
#include <sstream>

#include "debug.h"

#include "Form.h"
#include "FormFactory.h"

#include "TakeIfGenerator.h"

using namespace std;
using namespace Sloth;

TakeIfGenerator::TakeIfGenerator(Form const & _form, Form const & _pred)
  : args(advance(_form, _pred))
{
}

bool TakeIfGenerator::isNil() const
{
  return args.first.isNil() || args.second.isNil();
}

Form TakeIfGenerator::head() const
{
  TRACE_HEAD_START(args.first);
  TRACE_HEAD_START(args.second);

  if ( isNil() ) {
    Form rv = headFromNil();
    return rv;
  }

  Form rv = args.first.getHead();
  TRACE_HEAD_FINISH(rv);
  return rv;
}

Form TakeIfGenerator::tail() const
{
  if ( isNil() ) {
    return FormFactory::makeNil();
  }

  TakeIfGenerator * gen = new TakeIfGenerator(args.first.getTail(), 
					      args.second.getTail());
  return FormFactory::makeSequence(gen);
}

string TakeIfGenerator::toString() const
{
  stringstream s;
  s << "(takeif " << args.first << " " << args.second << ")";
  return s.str();
}

pair<Form, Form> TakeIfGenerator::advance(Form form, Form pred)
{
  while ( ! form.isNil() && ! pred.isNil() ) {
    Form f = pred.getHead();
    if ( ! f.hasBooleanValue() ) {
      // error
    }

    if ( f.getBooleanValue() ) {
      break;
    }

    form = form.getTail();
    pred = pred.getTail();
  }

  return std::pair<Form, Form>(form, pred);
}
