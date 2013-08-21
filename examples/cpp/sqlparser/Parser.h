// $Id: /home/I809989/test/cpp/parser/Parser.h#1 $
// $DateTime: Fri Apr 15 09:05:53 2011 $

#if ! defined(Parser_h)
#define Parser_h 1

#include <string>
#include <istream>
#include <stdexcept>
#include <vector>

#include "TokenStream.h"
#include "Expression.h"

namespace parser {

  class ParserException : public std::runtime_error
  {
  public:
    ParserException(std::string const & what);
  };

  /**
   * Parser
   *
   * Interface for parser type.  Also provides character buffering.
   */
  class Parser 
  {
  public:
    /**
     * parse
     *
     * Receive input and attempt to match it against some rules.
     *
     * @param s
     *
     */
    virtual Expression parse(TokenStream & tokens) const = 0;

  protected:

  private:
  };
 
  /**
   * Parser which always succeeds with zero width match.
   */
  class NullParser : public Parser
  {
  public:
    virtual Expression parse(TokenStream & tokens) const;
  };

}

#endif // not defined Parser_h
