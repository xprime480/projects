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

#define PARSER_FLAGS_NONE  0
#define PARSER_FLAGS_TRACE 1

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
     * @param tokens a stream from which to read tokens
     * @param flags  a set of flags to honor
     *
     */
    virtual Expression parse(TokenStream & tokens, int flags) const = 0;

  protected:

  private:
  };
 
  /**
   * Parser which always succeeds with zero width match.
   */
  class NullParser : public Parser
  {
  public:
    virtual Expression parse(TokenStream & tokens, int flags) const;
  };

}

#endif // not defined Parser_h
