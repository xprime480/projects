// $Id: /home/I809989/test/cpp/parser/SequenceOfParser.cpp#1 $
// $DateTime: Fri Apr 15 13:09:24 2011 $

#include "SequenceOfParser.h"

using namespace std;
using namespace parser;

SequenceOfParser::SequenceOfParser(vector<Parser *> const & _ps)
  : parsers(_ps)
{
}

Expression SequenceOfParser::parse(TokenStream & tokens) const
{
  Expression final;
  final.append(Expression(true));
  final.append(Expression());
  final.append(Expression(""));

  TokenStream::state_type state = tokens.getState();

  typedef vector<Parser *>::const_iterator iter;
  for ( iter i = parsers.begin() ; i != parsers.end() ; ++i ) {
    Expression result = (*i)->parse(tokens);
    if ( result ) {
      final.nth(1).append(result.nth(1));
      final.nth(2).addText(result.nth(2));
    }
    else {
      tokens.setState(state);
      return Expression(false);
    }
  }

  return final;
}
