#if ! defined(LazyInterp_h)
#define LazyInterp_h 1

#include <string>
#include <vector>

#include "LazyExpression.h"
#include "LazyForm.h"
#include "LazySeq.h"
#include "Token.h"

namespace lazy
{
  /**
   * LazyInterp
   *
   * Interpreter for the Sloth language.
   * 
   * Examples:
   *
   * If the sequence is not empty, then head holds M, tail()->head holds
   * V, and tail()->tail() lazily computes the remainder of the sequence.
   */
  class LazyInterp
  {
  public:
    /**
     * constructor
     */
    LazyInterp();

    /**
     * destructor
     */
    ~LazyInterp();

    /**
     * parse
     *
     * turn character input into an internal stack
     *
     * @param _spec the input
     *
     * @return result of parsing, either a sequence or an error
     *         message.
     */
    LazyForm * parse(char const * _spec);

    /**
     * parse
     *
     * turn character input into an internal stack
     *
     * @param _spec the input
     *
     * @return result of parsing, either a sequence or an error
     *         message.
     */
    LazyForm * parse(std::string & input);

    /**
     * parse
     *
     * turn internal token stream into an internal stack
     *
     * @param _spec the input
     *
     * @return result of parsing, either a sequence or an error
     *         message.
     */
    LazyForm * parse();

  private:
    LazySeq<Token> * tokens;	// pending unparsed tokens

    /**
     * processKeyword
     * 
     * process input that looks like a keyword name
     *
     * @return an error message or a lazy sequence form
     */
    LazyForm * processKeyword();


    /**
     * processSubexpr
     * 
     * process input that looks like a subexpression e.g. (* 2 3)
     *
     * @return an error message or a lazy sequence form
     */
    LazyForm * processSubexpr();

    /**
     * processTimes
     * 
     * process input that looks like a multiplication subexpression
     * e.g. (* 2 3)
     *
     * @return an error message or a lazy sequence form
     */
    LazyForm * processTimes(LazyExpression & ex);

    /**
     * processList
     * 
     * process input that looks like a number list e.g. [1 2 3]
     *
     * @return an error message or a lazy sequence form
     */
    LazyForm * processList();	// process [1 2 ...]

  public:
    /**
     * argToStream
     *
     * convert an input argument to a stream.  There are 2 types of
     * args:
     *	placeholder (_) is converted to a stream found by reading the
     *                  input
     *  integers        are converted to a stream of an infinite
     *                  repetition of the given integer
     *
     * @param arg the input
     * @param seq a place to put the output seq
     *
     * @return an error message or NULL
     *
     * TODO:  convert this to take advantage of the
     *        LazyIntSeq->getSequence() idiom.
     */
    LazyForm * argToStream(Token const & arg, LazySeq<int> *& seq);
  };
}

#endif // not defined LazyInterp_h
