
#include <iostream>
#include <sstream>

#include "FormFactory.h"
#include "IntegerGenerator.h"
#include "SequenceGenerator.h"

#include "Form.h"


using namespace std;
using namespace Sloth;


/*****************************************************/

Form::~Form()
{
}


string Form::toString() const
{
  static string error(": Internal error: unknown form type");
  stringstream s;
  s << __FUNCTION__  << error;
  throw runtime_error(s.str());

  return "";
}

Form Form::eval()
{
  static string error(": Internal error: unknown form type");
  stringstream s;
  s << __FUNCTION__  << error;
  throw runtime_error(s.str());

  return *this;
}

Form::FormType Form::getType() const
{
  return type;
}

bool Form::isNil() const
{
  return false;
}

bool Form::hasIntValue() const
{
  return false;
}

int Form::getIntValue() const
{
  static string error(": Internal error: form has no integer value");
  stringstream s;
  s << __FUNCTION__  << error;
  throw runtime_error(s.str());
}

bool Form::hasBooleanValue() const
{
  return false;
}

bool Form::getBooleanValue() const
{
  static string error(": Internal error: form has not boolean value");
  stringstream s;
  s << __FUNCTION__  << error;
  throw runtime_error(s.str());
}

bool Form::hasStringValue() const
{
  return false;
}

string Form::getStringValue() const
{
  static string error(": Internal error: form has no string value");
  stringstream s;
  s << __FUNCTION__  << error;
  throw runtime_error(s.str());
}

bool Form::isSequence() const
{
  return false;
}

Form Form::getHead() const
{
  static string error(": Internal error: form has no head");
  stringstream s;
  s << __FUNCTION__  << error;
  throw runtime_error(s.str());
}

Form Form::getTail() const
{
  static string error(": Internal error: form has no tail");
  stringstream s;
  s << __FUNCTION__  << error;
  throw runtime_error(s.str());
}

bool Form::isMessage() const
{
  return false;
}

string Form::getMessage() const
{
  static string error(": Internal error: form has no message value");
  stringstream s;
  s << __FUNCTION__  << error;
  throw runtime_error(s.str());
}

bool Form::isBlob() const
{
  return false;
}

void * Form::getBlobValue() const
{
  static string error(": Internal error: form has no blob value");
  stringstream s;
  s << __FUNCTION__  << error;
  throw runtime_error(s.str());
}

bool Form::isSymbol() const
{
  return false;
}

Form setValue(Form const & form)
{
  static string error(": Internal error: form is not settable");
  stringstream s;
  s << __FUNCTION__  << error;
  throw runtime_error(s.str());
}



#if 0
Form::Form()
  : type(FormType_NIL)
  , impl(0)
  , generator(false)
{
}

Form::Form(int _intvalue)
  : type(FormType_INTEGER)
  , impl(new int(_intvalue))
  , generator(false)
{
}

Form::Form(bool _boolvalue)
  : type(FormType_BOOLEAN)
  , impl(new bool(_boolvalue))
  , generator(false)
{
}

Form::Form(std::string const & _stringvalue, bool _message)
  : type(_message ? FormType_MESSAGE : FormType_STRING)
  , impl(new string(_stringvalue))
  , generator(false)
{
}

Form::Form(void * _blobvalue)
  : type(FormType_BLOB)
  , impl(_blobvalue)
  , generator(false)
{
}

Form::Form(IntegerGenerator * _intgenvalue)
  : type(_intgenvalue ? FormType_INTEGER : FormType_NIL)
  , impl(_intgenvalue)
  , generator(true)
{
}

Form::Form(SequenceGenerator * _seqgenvalue)
  : type(_seqgenvalue ? FormType_SEQUENCE : FormType_NIL)
  , impl(_seqgenvalue)
  , generator(true)
{
}

Form::Form(std::string const & _symbolname, Form const & _symbolValue)
  : type(FormType_SYMBOL)
  , impl(new SymbolForm(_symbolname, _symbolValue))
  , generator(false)
{
}

Form::Form(Form const & that)
{
  *this = that;
}

Form & Form::operator=(Form const & that)
{
  if ( this != &that ) {
    this->impl = that.impl;
  }

  return *this;
}

Form::~Form()
{
}

#endif

#if 0
string Form::toString() const
{
  stringstream s;

  switch ( type ) {
  case FormType_INTEGER:
    if ( generator ) {
      s << impl->toString();
    }
    else {
      s << *impl;
    }
    break;

  case FormType_BOOLEAN:
    {
      static string const trueValue("@t");
      static string const falseValue("@f");

      return (*(bool*)impl) ? trueValue : falseValue;
    }
    break;

  case FormType_STRING:
  case FormType_MESSAGE:
    s << impl.stringvalue;
    break;

  case FormType_SEQUENCE:
    s << impl.seqgenvalue->toString();
    break;

  case FormType_SYMBOL:
    s << impl.symbolvalue.name
      << " [=" << impl.symbolvalue.value.toString() << "]";
    break;

    break;

  case FormType_BLOB:
    s << "<<Blob: 0x" << impl.blobvalue << ">>";
    break;

  case FormType_NIL:
    {
      static string nil("<nil>");
      return s << nil;
    }
    break;

  default:
    
    break;
  }

  return s.str();
}

Form Form::eval()
{
  switch ( type ) {
  case FormType_INTEGER:
    if ( generator ) {
      return FormFactory::makeInt(impl.intgenvalue->value());
    }
    else {
      return *this;
    }
    break;

  case FormType_BOOLEAN:
  case FormType_STRING:
  case FormType_MESSAGE:
  case FormType_BLOB:
  case FormType_NIL:
    return *this;
    break;

  case FormType_SEQUENCE:
    return evaluateSequence();
    break;

  case FormType_SYMBOL:
    return impl.symbolValue.value.eval();
    break;

  default:
    
    break;
  }
}

bool Form::isNil() const
{
  return ( type == FormType_NIL ||
	   ( type == FormType_SEQUENCE && impl.genseqvalue->isNil() ) ||
	   ( type == FormType_SYMBOL && impl.symbolvalue.value.isNil() ) );
}

bool Form::hasIntValue() const
{
  return ( type == FormType_INTEGER ||
	   type == FormType_SYMBOL && impl.symbolvalue.value.hasIntValue() );
}

int Form::getIntValue() const
{
  int rv = numeric_limits<int>::max();

  switch ( type ) {
  case FormType_INTEGER:
    if ( generator ) {
      rv = impl.intgenvalue->value();
    } else {
      rv = impl.intvalue;
    }
    break;

  case FormType_BOOLEAN:
  case FormType_STRING:
  case FormType_MESSAGE:
  case FormType_SEQUENCE:
  case FormType_BLOB:
  case FormType_NIL:
    break;

  case FormType_SYMBOL:
    rv = impl.symbolvalue.value.getIntValue();
    break; 

  default:
    
    break;
  }

  return rv;
}

bool Form::hasBooleanValue() const
{
  return ( type == FormType_BOOLEAN ||
	   type == FormType_SYMBOL && 
	   impl.symbolvalue.value.hasBooleanValue() );
}

bool Form::getBooleanValue() const
{
  bool rv = false;

  switch ( type ) {
  case FormType_BOOLEAN:
    rv = impl.boolvalue;
    break;

  case FormType_INTEGER:
  case FormType_STRING:
  case FormType_MESSAGE:
  case FormType_SEQUENCE:
  case FormType_BLOB:
  case FormType_NIL:
    break;

  case FormType_SYMBOL:
    rv = impl.symbolvalue.value.getBooleanValue();
    break;

  default:
    
    break;
  }

  return rv; 
}

bool Form::hasStringValue() const
{
  return ( type == FormType_STRING ||
	   type == FormType_MESSAGE ||
	   type == FormType_SYMBOL && 
	   impl.symbolvalue.value.hasStringValue() );

}

string Form::getStringValue() const
{
  string rv = "";

  switch ( type ) {
  case FormType_STRING:
  case FormType_MESSAGE:
    rv = impl.stringvalue;
    break;

  case FormType_BOOLEAN:
  case FormType_INTEGER:
  case FormType_SEQUENCE:
  case FormType_BLOB:
  case FormType_NIL:
    break;

  case FormType_SYMBOL:
    rv = impl.symbolvalue.value.getStringValue();
    break;

  default:
    
    break;
  }

  return rv; 
}

bool Form::isSequence() const
{
  return ( type == FormType_NIL ||
	   type == FormType_SEQUENCE ||
	   type == FormType_SYMBOL && impl.symbolvalue.value.isSequence() );
}


Form Form::getHead() const
{
  Form rv;

  switch ( type ) {
  case FormType_SEQUENCE:
    rv = impl.seqgenvalue->head();
    break;

  case FormType_STRING:
  case FormType_MESSAGE:
  case FormType_BOOLEAN:
  case FormType_INTEGER:
  case FormType_BLOB:
  case FormType_NIL:
    {
      static string error ": Runtime error: type has no tail: ";
      stringstream s;
      s << __FUNCTION__  << error << type;
      rv = FormFactory::makeMessage(s.str());
    }
    break;

  case FormType_SYMBOL:
    rv = impl.symbolvalue.value.getHead();
    break;

  default:
    
    break;
  }
  
  return rv;
}

Form Form::getTail() const
{
  Form rv;

  switch ( type ) {
  case FormType_SEQUENCE:
    rv = impl.seqgenvalue->tail();
    break;

  case FormType_STRING:
  case FormType_MESSAGE:
  case FormType_BOOLEAN:
  case FormType_INTEGER:
  case FormType_BLOB:
    {
      static string error ": Runtime error: type has no tail: ";
      stringstream s;
      s << __FUNCTION__  << error << type;
      rv = FormFactory::makeMessage(s.str());
    }
    break;

  case FormType_NIL:
    rv = FormFactory::makeNil();
    break;

  case FormType_SYMBOL:
    rv = impl.symbolvalue.value.getHead();
    break;

  default:
    
    break;
  }
  
  return rv;
}

bool Form::isMessage() const
{
  return ( type == FormType_MESSAGE ||
	   type == FormType_SYMBOL && impl.symbolvalue.value.isMessage() );
}

std::string Form::getMessage() const
{
  string rv = "";

  switch ( type ) {
  case FormType_MESSAGE:
    rv = impl.stringvalue;
    break;

  case FormType_STRING:
  case FormType_BOOLEAN:
  case FormType_INTEGER:
  case FormType_SEQUENCE:
  case FormType_BLOB:
  case FormType_NIL:
    break;

  case FormType_SYMBOL:
    rv = impl.symbolvalue.value.getStringValue();
    break;

  default:
    
    break;
  }

  return rv; 
}

bool Form::isBlob() const
{
  bool v = ( type == FormType_BLOB ||
	     type == FormType_SYMBOL && impl.symbolvalue.value.isBlob() )
  return v;
}

void * Form::getBlobValue() const
{
  void * rv = 0;

  switch ( type ) {
  case FormType_BLOB:
    rv = impl.blobvalue;
    break;

  case FormType_STRING:
  case FormType_MESSAGE:
  case FormType_BOOLEAN:
  case FormType_INTEGER:
  case FormType_SEQUENCE:
  case FormType_NIL:
    break;

  case FormType_SYMBOL:
    rv = impl.symbolvalue.value.getBlobValue();
    break;

  default:
    break;
  }

  return rv; 
}

bool Form::isSymbol() const
{
  return ( type == FormType_SYMBOL );
}

Form Form::setValue(Form const & form)
{
  Form rv = "";

  switch ( type ) {
  case FormType_SYMBOL:
    impl.symbolvalue.value = form;
    rv = form;
    break;

  case FormType_MESSAGE:
  case FormType_STRING:
  case FormType_BOOLEAN:
  case FormType_INTEGER:
  case FormType_SEQUENCE:
  case FormType_BLOB:
  case FormType_NIL:
    
    break;

  default:
    {
      static string error ": Internal error: unknown form type";
      stringstream s;
      s << __FUNCTION__  << error;
      rv = FormFactory.makeMessage(s.str());
    }
    break;
  }

  return rv; 
}

Form Form::evaluateSequence() const
{
  static string const error1 = "SequenceFormImpl::eval expecting sequence, got ";
  stringstream s;

  vector<Form> values;

  Form f(this);
  if ( ! f.isSequence() ) {
    s << error1 << f;
    FormImpl * rv = new MessageFormImpl(s.str());
    EVAL_FINISH(rv);
    return rv;
  }

  while ( ! f.isNil() ) {
    Form h = f.getHead();
    values.push_back(h.eval());
    f = f.getTail();
  }

  Form * rv = FormFactory::makeSequence(new ListGenerator(values));
  EVAL_FINISH(rv);
  return rv;
}

#endif
