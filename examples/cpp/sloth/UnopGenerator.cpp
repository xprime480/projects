
#include <sstream>

#include "FormFactory.h"

#include "UnopGenerator.h"

using namespace std;
using namespace Sloth;

UnopGenerator::UnopGenerator(std::string const & _op, Form const & _arg)
  : op(_op)
  , arg(_arg)
{
  type = arg.isSequence() ? UnopArgs_Seq : UnopArgs_Non;
}

set<string> UnopGenerator::getUnopSet()
{
  static char const * opsRaw[] = {
    "!"
  };
  static size_t const nOps = sizeof(opsRaw) / sizeof (opsRaw[0]);
  static set<string> ops(opsRaw, opsRaw + nOps);

  return ops;
}


bool UnopGenerator::isNil() const
{
  bool rv = type == UnopArgs_Unknown;

  if ( type == UnopArgs_Seq ) {
    rv |= arg.isNil();
  }

  return rv;
}

Form UnopGenerator::head() const
{
  if ( isNil() ) {
    return headFromNil();
  }

  switch ( type ) { 
  case UnopArgs_Unknown:
    {
      stringstream s;
      s << "Unknown argument types to operator '" << op
	<< "':  (<" << arg << ">)";
      return FormFactory::makeMessage(s.str());
    }
    break;

  case UnopArgs_Seq:
    return eval(arg.getHead());
    break;

  case UnopArgs_Non:
    return eval(arg);
    break;
	  
  default:
    break;
  }

  stringstream s;
  s << "Internal error at " << __FILE__ << ", " << __LINE__;
  return FormFactory::makeMessage(s.str());
}

Form UnopGenerator::tail() const
{
  if ( isNil() ) {
    return FormFactory::makeNil();
  }


  switch ( type ) { 
  case UnopArgs_Unknown:
    return FormFactory::makeNil();
    break;
    
  case UnopArgs_Seq:
    {
      UnopGenerator * gen = new UnopGenerator(op, arg.getTail());
      return FormFactory::makeSequence(gen);
    }
    break;

  case UnopArgs_Non:
    return FormFactory::makeNil();
    break;

  default:

    break;
  }

    {
      stringstream s;
      s << "Internal error at " << __FILE__ << ", " << __LINE__;
      return FormFactory::makeMessage(s.str());
    }
}

string UnopGenerator::toString() const
{
  stringstream s;
  s << "(" << op << " " << arg << ")";
  return s.str();
}

Form UnopGenerator::eval(Form const & a) const
{
  static set<string> ops = getUnopSet();
  stringstream s;

  if ( ops.find(op) == ops.end() ) {
    s << "Unknown binary operator: '" << op << "'";
    return FormFactory::makeMessage(s.str());
  }

  if ( op != "!" ) {
    s << "Internal error at " << __FILE__ << " " << __LINE__
      << "op '" << op << "'";
    return FormFactory::makeMessage(s.str());
  }

  Form::FormType t = a.getType();
  switch ( t ) {
  case Form::FormType_INTEGER:
    {
      int i = a.getIntValue();
      return FormFactory::makeInt(-i);
    }
    break;

  case Form::FormType_BOOLEAN:
    {
      bool b = a.getBooleanValue();
      return FormFactory::makeBoolean(!b);
    }
    break;

  case Form::FormType_STRING:
    {
      Form f = a;
      return eval(f.eval());
    }
    break;

  case Form::FormType_SEQUENCE:
  case Form::FormType_SYMBOL:
  case Form::FormType_MESSAGE:
  case Form::FormType_BLOB:
  default:
    {
      s << "operator '" << op << "' not supported for value" << a;
      return FormFactory::makeMessage(s.str());
    }
    break;
  };

  s << "Internal error at " << __FILE__ << " " << __LINE__;
  return FormFactory::makeMessage(s.str());
}
