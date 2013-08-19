#if ! defined(LazyExpression_h)
#define LazyExpression_h 1

#include <vector>
#include <string>

#include "LazySeq.h"
#include "Token.h"

namespace lazy
{
  class LazyForm;
  class TokenStream;

  /**
   * LazyExpression
   *
   * This class represents an expression in the Lazy language.
   */
  class LazyExpression
  {
  public:
    /**
     * constructor
     *
     * Reads a series of tokens and constructs an expression
     *
     * @param _tokens program source
     */
    LazyExpression(LazySeq<Token> *& _tokens);

    /**
     * destructor
     */
    ~LazyExpression();

    /**
     * getResult
     *
     * Returns a form representing the state of the parsing.
     *
     * @result NULL if no error, else an error form.
     */
    LazyForm * getResult() const;

    /**
     * getOp
     *
     * Get the operation this expression contains
     *
     * @return the text representation of the form
     */
    std::string const & getOp() const;

    /**
     * getArgs
     *
     * Get a list of the arguments to this expression
     *
     * @return a vector of tokens to this expression
     */
    std::vector<Token> const & getArgs() const;
  
  protected:
  private:
    std::vector<Token> args;	// arguments to this expression
    std::string op;		// operator to this expression

    LazySeq<Token> *& tokens;	// input
    LazyForm * result;		// processing status

    LazyForm * readArgs();	// read the arguments to a form
    LazyForm * countPlaceholders(); // count the number of arguments
				    // that are placeholders for a sequence
  };
}

#endif // not defined LazyExpression_h
