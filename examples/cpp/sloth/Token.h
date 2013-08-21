#if ! defined(Sloth_Token_h)
#define Sloth_Token_h 1

#include <string>

namespace Sloth
{
  /**
   * Token
   *
   * This class represents a token scanned from an input source.
   */
  class Token
  {
  public:
    /**
     * constructor 
     */
    Token()
      : type(TT_UNKNOWN)
    {
    }

    /**
     * known token types
     */
    enum { TT_UNKNOWN = 0,

	   TT_INTEGER,
	   TT_STRING,
	   TT_SYMBOL,
	   TT_BOOLEAN,

	   TT_KEYWORD,
	   TT_OPERATOR,
	   TT_LPAREN,
	   TT_RPAREN,
	   TT_LSQUARE,
	   TT_RSQUARE,
	   TT_LCURLY,
	   TT_RCURLY,
	   TT_PLACEHOLDER
    } type;

    std::string contents;	// text as scanned

  };
}

/**
 * operator<<
 *
 * send a representation of the token to a stream.
 *
 * @param os the stream
 * @param t  a token
 *
 * @return the input stream
 */
template <typename OS>
OS & operator<<(OS & os, Sloth::Token const & t)
{
  os << t.contents;
  return os;
}

#endif // not defined Sloth_Token_h
