#if ! defined(Sloth_Expression_h)
#define Sloth_Expression_h 1

#include <vector>
#include <string>

#include "Form.h"
#include "LazySeq.h"
#include "Token.h"

namespace Sloth
{
  class TokenStream;

  /**
   * Expression
   *
   * This class represents an expression in the Lazy language.
   */
  class Expression
  {
  public:
    /**
     * constructor
     *
     * Reads a series of tokens and constructs an expression
     *
     * @param _tokens program source
     */
    Expression(LazySeq<Token> *& _tokens);

    /**
     * destructor
     */
    ~Expression();

    /**
     * getResult
     *
     * Returns a form representing the state of the parsing.
     *
     * @result NULL if no error, else an error form.
     */
    Form getResult() const;

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
    Form result;		// processing status

    Form * readArgs();		// read the arguments to a form
    Form * countPlaceholders(); // count the number of arguments
				    // that are placeholders for a sequence
  };
}

#endif // not defined Sloth_Expression_h
