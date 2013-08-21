#if ! defined(Lazy_Form_h)
#define Lazy_Form_h 1

#include <set>
#include <string>

namespace Sloth
{
  class FormFactory;
  class IntegerGenerator;
  class SequenceGenerator;
  class Form;

  struct SymbolFormTag {};

  struct SymbolForm {
    std::string   name;
    Form const  * value;

    SymbolForm(std::string const & _name, Form const & _value)
      : name(_name)
      , value(&_value)
    {
    }
  };

  /**
   * Form
   *
   * This class holds a printable form, either a text or a sequence.
   * 
   */
  class Form
  {
  public :
    enum FormType {
      FormType_INTEGER,
      FormType_BOOLEAN,
      FormType_STRING,
      FormType_SEQUENCE,
      FormType_SYMBOL,
      FormType_MESSAGE,
      FormType_BLOB,

      // implementation forms

      FormType_NIL,
    };

    Form(FormType _type);

    virtual ~Form();

    virtual std::string toString() const;

    virtual Form eval();

    virtual FormType getType() const;

    virtual bool isNil() const;

    virtual bool hasIntValue() const;
    virtual int getIntValue() const;

    virtual bool hasBooleanValue() const;
    virtual bool getBooleanValue() const;

    virtual bool hasStringValue() const;
    virtual std::string getStringValue() const;

    virtual bool isSequence() const;
    virtual Form getHead() const;
    virtual Form getTail() const;

    virtual bool isMessage() const;
    virtual std::string getMessage() const;

    virtual bool isBlob() const;
    virtual void * getBlobValue() const;

    virtual bool isSymbol() const;
    virtual Form setValue(Form const & form);

  private :
    Form(Form const & form);
    Form & operator=(Form const & form);

    FormType const type;

    friend class FormFactory;

    mutable size_t refs;

    bool dead;

    static std::set<Form *> live;

    static void gc();

  };

#if 0
  class OldForm
  {
  public:
    Form();

    Form(int _intvalue);

    Form(bool _boolvalue);

    explicit Form(std::string const & _stringvalue, bool _message = false);

    Form(void * _blobvalue);

    Form(IntegerGenerator * _intgenvalue);

    Form(SequenceGenerator * _seqgenvalue);

    Form(std::string const & _symbolname, Form const & _symbolValue);

    Form(Form const & that);

    Form & operator=(Form const & that);

    /**
     * destructor
     */
    ~Form();

    /**
     * toString
     *
     * turn the form into a printable representation.
     */

  private:
    FormType                type;
    std::shared_ptr<void>   impl;
    bool                    generator;
  };

  Form evaluateSequence();
#endif
}

#if 0
template <typename _OS>
_OS & operator<<(_OS & os, Sloth::Form const & form)
{
  os << form.toString();
  return os;
}
#endif

#endif // not defined Lazy_Form_h
