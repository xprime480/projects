#if ! defined(SliceGenerator_h)
#define SliceGenerator_h 1

#include "SequenceGenerator.h"

namespace Sloth
{
  class SliceGenerator : public SequenceGenerator 
  {
  public:
    /**
     * constructor
     *
     * @param _start the first value (The sequence is empty if this
     *               value is >= the stop value)
     * @param _stop  one beyond the last value
     * @param _step  the increment between each value
     */
    SliceGenerator(int _start, int _stop, int _step = 1);

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
    int start;
    int stop;
    int step;
  };
}

#endif // not defined SliceGenerator_h
