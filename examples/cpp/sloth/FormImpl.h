#if ! defined(FormImpl_h)
#define FormImpl_h 1

#include "Form.h"

namespace Sloth
{
#if 0
  class FormFactory;
#endif

  template <typename T>
  class FormImpl : public Form {
  public:
    virtual ~FormImpl() = 0;
  protected :
  private:
  };


#if 0
  class FormImpl
  {
  public:
    FormImpl(Form::FormType _type);

    virtual ~FormImpl();

    virtual std::string toString() const = 0;

    virtual FormImpl * eval() = 0;

    Form::FormType getType() const;

    virtual bool isNil() const;

    virtual bool hasIntValue() const;

    virtual int getIntValue() const;

    virtual bool hasBooleanValue() const;

    virtual bool getBooleanValue() const;

    virtual bool hasStringValue() const;

    std::string getStringValue() const;

    virtual bool isSequence() const;

    virtual Form getHead() const;

    virtual Form getTail() const;
  
    virtual bool isMessage() const;

    std::string getMessage() const;

    virtual bool isBlob() const;

    virtual void * getBlobValue() const;

    virtual bool isSymbol() const;

    virtual Form setValue(Form const & form);

    /**
     * any overrides of the following functions must either call this
     * version or ignore the refcount.
     */
    virtual void incref() const;

    virtual void decref() const;
    
  private:
  };
#endif
}

#endif // not defined FormImpl_h
