
#include <map>
#include <stdexcept>
#include <sstream>

#include "debug.h"

#include "FixedSequenceGenerator.h"
#include "Form.h"
#include "FormImpl.h"
#include "NilFormImpl.h"
#include "Infinite.h"
#include "ListGenerator.h"
#include "Utils.h"

#include "FormFactory.h"

using namespace std;
using namespace Sloth;

namespace
{
  /****************************/

  class NilFormImpl : public FormImpl<NilFormTag>
  {
  public:
    static NilFormImpl * getInstance();

    virtual void incref() const 
    {
      cerr << "nop incref" << endl;
    }

    virtual void decref() const 
    {
      cerr << "nop decref" << endl;
    }

  private:
    NilFormImpl();

    virtual ~NilFormImpl() {}
  };

  /****************************/

  class StringFormImpl : public FormImpl<std::string>
  {
  public:
    StringFormImpl(string const & v, 
		   Form::FormType _type = Form::FormType_STRING);

  private:
    string value;
  };

  /****************************/

  class BlobFormImpl : public FormImpl<void *>
  {
  public:
    BlobFormImpl(void * _value, void (*_handler)(void*));

    virtual ~BlobFormImpl();

  private:
    void * value;
    void (*handler)(void*);
  };

  /****************************/

  class MessageFormImpl : public StringFormImpl
  {
  public:
    MessageFormImpl(string const & message);

  };

  /****************************/

  class IntFormImpl : public FormImpl<int>
  {
  public:
    IntFormImpl(int v);

  private:
    int value;
  };

  /****************************/

  class LazyIntFormImpl : public FormImpl<IntegerGenerator *>
  {
  public:
    LazyIntFormImpl(IntegerGenerator * gen);

  private:
    IntegerGenerator * generator;
  };

  /****************************/

  class SequenceFormImpl : public FormImpl<SequenceGenerator *>
  {
  public:
    SequenceFormImpl(SequenceGenerator * _gen);

    virtual ~SequenceFormImpl();

    virtual Form getTail() const;

  private:
    SequenceGenerator * generator;
  };

  /****************************/

  class SymbolFormImpl : public FormImpl<SymbolFormTag>
  {
  public:
    SymbolFormImpl(string const & _name);

    virtual Form getTail() const;

    virtual Form setValue(Form const & form);

    virtual void incref() const 
    {
      cerr << "nop incref" << endl;
    }

    virtual void decref() const 
    {
      cerr << "nop decref" << endl;
    }

  private:
    string const name;
    Form value;
  };

  /****************************/

  class BooleanFormImpl : public FormImpl<bool>
  {
  public:

    static BooleanFormImpl * getInstance(bool _value);

    virtual void incref() const
    {
      cerr << "nop incref" << endl;
    }

    virtual void decref() const
    {
      cerr << "nop decref" << endl;
    }

  private:
    bool const value;

    BooleanFormImpl(bool _value);

    virtual ~BooleanFormImpl() {}
  };

}

#if 0
void FormImpl::gc()
{
  static size_t interval = 100;
  if ( live.size() >= interval ) {
    cerr << "beginning gc()" << endl;
    set<FormImpl *> temp;
    set<FormImpl *>::iterator iter;
    for ( iter = live.begin() ; iter != live.end() ; ++iter ) {
      FormImpl * impl = *iter;
      if ( impl && impl->refs > 0 ) {
	temp.insert(impl);
      }
      else {
	cerr << " deleting " << impl << endl;
	delete impl;
      }
    }
    live = temp;
    cerr << "ending gc()" << endl;
  }
  while ( live.size() >= interval ) {
    interval *= 2;
  }
}
#endif

/*******************************************************************
 *
 * Implementation for NilFormImpl
 *
 *******************************************************************/

NilFormImpl::NilFormImpl()
  : FormImpl(Form::FormType_SEQUENCE)
{
}

NilFormImpl * NilFormImpl::getInstance()
{
  static NilFormImpl * theInstance = new NilFormImpl();
  return theInstance;
}

/*******************************************************************
 *
 * Implementation for StringFormImpl
 *
 *******************************************************************/

StringFormImpl::StringFormImpl(string const & v, Form::FormType _type)
  : FormImpl(_type)
  , value(v)
{
}

/*******************************************************************
 *
 * Implementation for BlobFormImpl
 *
 *******************************************************************/

BlobFormImpl::BlobFormImpl(void * _value, void(*_handler)(void*))
  : FormImpl(Form::FormType_BLOB)
  , value(_value)
  , handler(_handler)
{
}

BlobFormImpl::~BlobFormImpl()
{
  handler(value);
  value = 0;
}


/*******************************************************************
 *
 * Implementation for MessageFormImpl
 *
 *******************************************************************/

MessageFormImpl::MessageFormImpl(string const & message)
  : StringFormImpl(message, Form::FormType_MESSAGE)
{
}

/*******************************************************************
 *
 * Implementation for IntFormImpl
 *
 *******************************************************************/

IntFormImpl::IntFormImpl(int v)
  : FormImpl(Form::FormType_INTEGER)
  , value(v)
{
}

/*******************************************************************
 *
 * Implementation for IntFormImpl
 *
 *******************************************************************/

LazyIntFormImpl::LazyIntFormImpl(IntegerGenerator * gen)
  : FormImpl(Form::FormType_INTEGER)
  , generator(gen)
{
}

/*******************************************************************
 *
 * Implementation for SequenceFormImpl
 *
 *******************************************************************/

SequenceFormImpl::SequenceFormImpl(SequenceGenerator * _gen)
  : FormImpl(Form::FormType_SEQUENCE)
  , generator(_gen)
{
}

SequenceFormImpl::~SequenceFormImpl()
{
  delete generator;
}

Form SequenceFormImpl::getHead() const
{
  return generator->head();
}

Form SequenceFormImpl::getTail() const
{
  return generator->tail();
}

/*******************************************************************
 *
 * Implementation for SymbolFormImpl
 *
 *******************************************************************/
    
SymbolFormImpl::SymbolFormImpl(string const & _name)
  : FormImpl(Form::FormType_SYMBOL)
  , name(_name)
{
}

Form SymbolFormImpl::getHead() const
{
  return value.getHead();
}

Form SymbolFormImpl::getTail() const
{
  return value.getTail();
}

Form SymbolFormImpl::setValue(Form const & form)
{
  value = form;
  return form;
}

/*******************************************************************
 *
 * Implementation for BooleanFormImpl
 *
 *******************************************************************/

BooleanFormImpl * BooleanFormImpl::getInstance(bool _value)
{
  static BooleanFormImpl * const trueValue  = new BooleanFormImpl(true);
  static BooleanFormImpl * const falseValue = new BooleanFormImpl(false);

  return _value ? trueValue : falseValue;
}

BooleanFormImpl::BooleanFormImpl(bool _value)
  : FormImpl(Form::FormType_BOOLEAN)
  , value(_value)
{
}

/*******************************************************************
 *
 * Implementation for FormFactory
 *
 *******************************************************************/

void FormFactory::incref(FormImpl const * impl)
{
  if ( impl ) {
    impl->incref();
  }
}

void FormFactory::decref(FormImpl const * impl)
{
  if ( impl ) {
    impl->decref();
  }
}

Form FormFactory::makeNil()
{
  return NilFormImpl::getInstance();
}

Form FormFactory::makeMessage(string const & message)
{
  Form f(new MessageFormImpl(message));
  return f;
}

Form FormFactory::makeInt(int value)
{
  Form f(new IntFormImpl(value));
  return f;
}

Form FormFactory::makeInt(IntegerGenerator * generator)
{
  Form f(new LazyIntFormImpl(generator));
  return f;
}

Form FormFactory::makeString(string const & value)
{
  Form f(new StringFormImpl(value));
  return f;
}

Form FormFactory::makeBlob(void * _value, void(*_handler)(void*))
{
  Form f(new BlobFormImpl(_value, _handler));
  return f;
}


Form FormFactory::makeSequence(SequenceGenerator * generator)
{
  Form f;
  if ( generator ) {
    f = new SequenceFormImpl(generator);
  }
  else {
    f = makeNil();
  }
  return f;
}

Form FormFactory::makeSymbol(string const & name)
{
  static map<string, SymbolFormImpl *> symbols;
  if ( symbols.find(name) == symbols.end() ) {
    symbols[name] = new SymbolFormImpl(name);
  }
  Form f(symbols[name]);
  return f;
}

Form FormFactory::makeBoolean(bool value)
{
  Form f(BooleanFormImpl::getInstance(value));
  return f;
}
