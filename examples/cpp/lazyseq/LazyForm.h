#if ! defined(LazyForm_h)
#define LazyForm_h 1

#include <string>

#include "LazySeq.h"

namespace lazy
{
  /**
   * LazyForm
   *
   * This class holds a printable form, either a text or a sequence.
   * 
   */
  class LazyForm
  {
  public:
    /**
     * destructor
     */
    virtual ~LazyForm();

    /**
     * print
     *
     * send a representation of the form to stdout 
     */
    virtual void print() = 0;
  };

  /**
   * LazyErrorForm
   *
   * This class represents an error in the Lazy interpreter.
   */
  class LazyErrorForm : public LazyForm
  {
  public:
    /**
     * constructor
     *
     * @param _m the error message
     */
    LazyErrorForm(std::string const & _m);

    /**
     * print
     *
     * See base class for documentation.
     */ 
    virtual void print();

  private:
    std::string message;	// the error message
  };

  /**
   * LazyIntStream
   *
   * This class wraps a lazy stream.
   */
  class LazyIntStream : public LazyForm
  {
  public:
    /**
     * constructor
     *
     * @param _seq the input sequence to be wrapped
     */
    LazyIntStream(LazySeq<int> * _seq);

    /**
     * destructor
     */
    virtual ~LazyIntStream();

    /**
     * print
     *
     * See base class for documentation.
     */ 
    virtual void print();

    /**
     * getSequence
     *
     * return the underlying sequence
     */
    virtual LazySeq<int> * getSequence();

  private:
    LazySeq<int> * seq;		// a lazy integer sequence
  };
}

#endif // not defined LazyForm_h
