// $Id: /home/I809989/test/cpp/sqlparser/SqlTokenStream.h#1 $
// $DateTime: Wed Nov  9 11:03:53 2011 $

#if ! defined(SqlTokenStream_h)
#define SqlTokenStream_h 1

#include "BasicTokenStream.h"

namespace parser {
  class SqlTokenStream : public BasicTokenStream
  {
  public:
    /**
     * constructor
     *
     * Create a token stream from a character stream.  Parses things
     * in the SQL way
     *
     * @param _c a character stream
     *
     */
    SqlTokenStream(CharacterStream & _c);
  };
}

#endif // not defined SqlTokenStream_h
