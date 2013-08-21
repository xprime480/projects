// $Id: /home/I809989/test/cpp/parser/SequenceOfParser.cpp#1 $
// $DateTime: Fri Apr 15 13:09:24 2011 $

#include "SequenceOfParser.h"

using namespace std;
using namespace parser;

SequenceOfParser::SequenceOfParser(vector<Parser *> const & _ps)
  : parsers(_ps)
{
}

ParseResult SequenceOfParser::parse(TokenStream & tokens) const
{
  ParseResult final;
  TokenStream::state_type state = tokens.getState();

  typedef vector<Parser *>::const_iterator iter;
  for ( iter i = parsers.begin() ; i != parsers.end() ; ++i ) {
    ParseResult result = (*i)->parse(tokens);
    if ( result ) {
      final.append(result);
    }
    else {
      tokens.setState(state);
      return ParseResult(false);
    }
  }

  return final;
}
