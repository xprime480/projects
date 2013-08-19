
#include <sstream>

#include "LazyExpression.h"

#include "LazyForm.h"
#include "TokenStream.h"

using namespace std;
using namespace lazy;

LazyExpression::LazyExpression(LazySeq<Token> *& _tokens)
  : tokens(_tokens)
  , result(NULL)
{
  tokens = TokenStream::cdr(tokens);
  if ( tokens->empty ) {
    result = new LazyErrorForm("Unexpected end of input in subexpression");
    return;
  }

  Token * t = &tokens->head;
  op = t->contents;
  if ( t->type != Token::TT_BINARY_OPERATOR ) {
    stringstream s;
    s << "Unknown operator: '" << op << "'";
    result = new LazyErrorForm(s.str());
    return;
  }
  size_t expectedArgCount = 2;

  tokens = TokenStream::cdr(tokens);

  readArgs();
  if ( result ) {
    return;
  }
  if ( args.size() != expectedArgCount ) {
    stringstream s;
    s << "Operator <" << op
      << "> expected " << expectedArgCount
      << " args, got " << args.size();
    result = new LazyErrorForm(s.str());
    return;
  }
}

LazyExpression::~LazyExpression()
{
  delete result;
}

LazyForm * LazyExpression::getResult() const
{
  return result;
}

string const & LazyExpression::getOp() const
{
  return op;
}

vector<Token> const & LazyExpression::getArgs() const
{
  return args;
}

LazyForm * LazyExpression::readArgs()
{
  while ( true ) {
    if ( tokens->empty ) {
      stringstream s;
      s << "operator: '" << op << "' not terminated";
      return new LazyErrorForm(s.str());
    }
    if ( tokens->head.type == Token::TT_RPAREN ) {
      break;
    }

    args.push_back(tokens->head);
    tokens = TokenStream::cdr(tokens);
  }

  tokens = TokenStream::cdr(tokens);

  return NULL;
}

