
#include <sstream>

#include "Expression.h"

#include "Form.h"
#include "FormFactory.h"
#include "TokenStream.h"

using namespace std;
using namespace Sloth;

Expression::Expression(LazySeq<Token> *& _tokens)
  : tokens(_tokens)
  , result(NULL)
{
  tokens = TokenStream::cdr(tokens);
  if ( tokens->empty ) {
    string const msg("Unexpected end of input in subexpression");
    result = FormFactory::makeMessage(msg);
    return;
  }

  Token tOp = tokens->head;
  op = tOp.contents;
  if ( tOp.type != Token::TT_OPERATOR ) {
    stringstream s;
    s << "Unknown operator: '" << op << "'";
    result = FormFactory::makeMessage(s.str());
    return;
  }
  size_t expectedArgCount = 2;

  tokens = TokenStream::cdr(tokens);

  readArgs();
  if ( ! result.isNil() ) {
    return;
  }
  if ( args.size() != expectedArgCount ) {
    stringstream s;
    s << "Operator <" << op
      << "> expected " << expectedArgCount
      << " args, got " << args.size();
    result = FormFactory::makeMessage(s.str());
    return;
  }
}

Expression::~Expression()
{
}

Form Expression::getResult() const
{
  return result;
}

string const & Expression::getOp() const
{
  return op;
}

vector<Token> const & Expression::getArgs() const
{
  return args;
}

Form * Expression::readArgs()
{
  return NULL;
}

