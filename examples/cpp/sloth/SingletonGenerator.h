#if ! defined(SingletonGenerator_h)
#define SingletonGenerator_h 1

#include "SequenceGenerator.h"

namespace Sloth
{
  class SingletonGenerator : public SequenceGenerator 
  {
  public:
    /**
     * constructor
     *
     */
    SingletonGenerator(int _value);

    /**
     * isNil()
     *
     * See base class for documentation.
     */ 
    virtual bool isNil() const;

    /**
     * head
     *
     * See base class for documentation.
     */ 
    virtual Form head() const;

    /**
     * tail
     *
     * See base class for documentation.
     */ 
    virtual Form tail() const;

    virtual std::string toString() const;

  private:
    int value;
  };
}

#endif // not defined SingletonGenerator_h
