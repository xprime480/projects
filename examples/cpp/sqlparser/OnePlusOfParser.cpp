// $Id: /home/I809989/test/cpp/parser/OnePlusOfParser.cpp#1 $
// $DateTime: Fri Apr 15 14:14:43 2011 $

#include "OnePlusOfParser.h"

using namespace std;
using namespace parser;

OnePlusOfParser::OnePlusOfParser(Parser * _p)
  : parser(_p)
{
}

ParseResult OnePlusOfParser::parse(TokenStream & tokens) const
{
  TokenStream::state_type state = tokens.getState();

  ParseResult final(false);
  ParseResult result = parser->parse(tokens);

  while ( result.success ) {
    size_t len = result.match.size();
    if ( len == 0 ) {
      tokens.setState(state);
      throw ParserException("OnePlusOfParser: zero length part");
    }

    final.success = true;
    final.match += result.match;
    final.parts.push_back(result.match);

    TokenStream::state_type lastGood = tokens.getState();
    result = parser->parse(tokens);
    if ( ! result.success ) {
      tokens.setState(lastGood);
    }
  }

  if ( ! final.success ) {
    tokens.setState(state);
  }

  return final;
}
