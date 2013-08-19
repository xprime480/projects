#include <cstdlib>
#include <ctype.h>
#include <iostream>
#include <map>
#include <sstream>

#include "LazyInterp.h"

#include "AnonSeq.h"
#include "Appender.h"
#include "Counter.h"
#include "Dropper.h"
#include "Fibonacci.h"
#include "Forever.h"
#include "Hamming.h"
#include "LazySeq.h"
#include "LazySeqUtils.h"
#include "List.h"
#include "Naturals.h"
#include "Taker.h"
#include "TokenStream.h"
#include "Transformer2.h"
#include "While2.h"

using namespace std;
using namespace lazy;

namespace
{
  struct KwProcessor 
  {
  public:
    virtual ~KwProcessor()
    {
    }

    virtual LazyForm * make(string const & kw, 
			    LazySeq<Token> *& tokens,
			    LazyInterp * interp) = 0;
  };

  template <typename T>
  struct BasicMaker : public KwProcessor
  {
    LazyForm * make(string const & kw, 
		    LazySeq<Token> *& tokens,
		    LazyInterp * interp)
    {
      LazySeq<int> * z = new T();
      TRACEALLOC(z);
      LazySeqStat::addref(z);
      LazyForm * f = new LazyIntStream(z);
      LazySeqStat::deref(z);
      return f;
    }
  };

  template <typename T>
  struct IntMaker : public KwProcessor
  {
    LazyForm * make(string const & kw, 
		    LazySeq<Token> *& tokens,
		    LazyInterp * interp)
    {
      if ( tokens->empty ) {
	stringstream s;
	s << "Unexpected end of input after '" << kw << "'";
	return new LazyErrorForm(s.str());
      }

      Token const & t = tokens->head;
      if ( t.type != Token::TT_INTEGER ) {
	stringstream s;
	s << "Expected an integer after '" << kw << "', got " << t.contents;
	return new LazyErrorForm(s.str());
      }
      int n = atoi(t.contents.c_str());
      tokens = TokenStream::cdr(tokens);
      
      LazySeq<int> * z = new T(n);
      TRACEALLOC(z);
      LazySeqStat::addref(z);
      LazyForm * f = new LazyIntStream(z);
      LazySeqStat::deref(z);
      return f;
    }
  };

  template <typename T>
  struct StreamMaker : public KwProcessor
  {
    LazyForm * make(string const & kw, 
		    LazySeq<Token> *& tokens,
		    LazyInterp * interp)
    {
      if ( tokens->empty ) {
	stringstream s;
	s << "Unexpected end of input after '" << kw << "'";
	return new LazyErrorForm(s.str());
      }

      LazyForm * subform = interp->parse();
      LazyIntStream * s = dynamic_cast<LazyIntStream *>(subform);
      if ( ! s ) {
	return subform;
      }

      LazySeq<int> * z = new T(s->getSequence());
      TRACEALLOC(z);
      LazySeqStat::addref(z);
      delete subform;
      LazyForm * f = new LazyIntStream(z);
      LazySeqStat::deref(z);
      return f;
    }
  };

  template <typename T>
  struct StreamIntMaker : public KwProcessor
  {
    LazyForm * make(string const & kw, 
		    LazySeq<Token> *& tokens,
		    LazyInterp * interp)
    {
      if ( tokens->empty ) {
	stringstream s;
	s << "Unexpected end of input after '" << kw << "'";
	return new LazyErrorForm(s.str());
      }

      Token const & t = tokens->head;
      if ( t.type != Token::TT_INTEGER ) {
	stringstream s;
	s << "Expected an integer after '" << kw << "', got " << t.contents;
	return new LazyErrorForm(s.str());
      }

      int n = atoi(t.contents.c_str());
      tokens = TokenStream::cdr(tokens);
      LazyForm * subform = interp->parse();
      LazyIntStream * s = dynamic_cast<LazyIntStream *>(subform);
      if ( ! s ) {
	return subform;
      }

      LazySeq<int> * z = new T(s->getSequence(), n);
      TRACEALLOC(z);
      LazySeqStat::addref(z);
      delete subform;
      LazyForm * f = new LazyIntStream(z);
      LazySeqStat::deref(z);
      return f;
    }
  };

  template <typename T>
  struct StreamStreamMaker : public KwProcessor
  {
    LazyForm * make(string const & kw, 
		    LazySeq<Token> *& tokens,
		    LazyInterp * interp)
    {
      LazyForm * subform1 = interp->parse();
      LazyIntStream * s1 = dynamic_cast<LazyIntStream *>(subform1);
      if ( ! s1 ) {
	return subform1;
      }

      LazyForm * subform2 = interp->parse();
      LazyIntStream * s2 = dynamic_cast<LazyIntStream *>(subform2);
      if ( ! s2 ) {
	return subform2;
      }


      LazySeq<int> * z = new T(s1->getSequence(), s2->getSequence());
      TRACEALLOC(z);
      LazySeqStat::addref(z);
      delete subform1;
      delete subform2;
      LazyForm * f = new LazyIntStream(z);
      LazySeqStat::deref(z);
      return f;
    }
  };

  struct WhileMaker : public KwProcessor
  {
    LazyForm * make(string const & kw, 
		    LazySeq<Token> *& tokens,
		    LazyInterp * interp)
    {
      if ( tokens->empty ) {
	stringstream s;
	s << "Unexpected end of input after '" << kw << "'";
	return new LazyErrorForm(s.str());
      }

      Token const & t = tokens->head;
      if ( t.type != Token::TT_LPAREN) {
	stringstream s;
	s << "Expected a filter after '" << kw << "', got " << t.contents;
	return new LazyErrorForm(s.str());
      }

      LazyExpression ex(tokens);
      LazyForm * f = ex.getResult();
      if ( f ) {
	return f;
      }

      vector<Token> const & args = ex.getArgs();
      LazySeq<int> * s1;
      f = interp->argToStream(args[0], s1);
      if ( f ) {
	return f;
      }
      LazySeq<int> * s2;
      f = interp->argToStream(args[1], s2);
      if ( f ) {
	return f;
      }

      string const & op = ex.getOp();
      LazySeq<bool> * c = NULL;
      if ( op == "<" ) {
	c = new Transformer2<less<int> >(s1, s2);
      }
      else {
	stringstream s;
	s << "Filter operator '" << op << "' is unknown";
	return new LazyErrorForm(s.str());
      }
      TRACEALLOC(c);
      LazySeqStat::addref(c);

      LazySeq<int> * ss = args[1].type == Token::TT_PLACEHOLDER ? s2 : s1;
      LazySeq<int> * z = new While2<int>(c, ss);
      TRACEALLOC(z);
      LazySeqStat::addref(z);
      f = new LazyIntStream(z);
      LazySeqStat::deref(z);
      LazySeqStat::deref(c);
      LazySeqStat::deref(s2);
      LazySeqStat::deref(s1);

      return f;
    }
  };

  struct RecurseMaker : public KwProcessor
  {
    LazyForm * make(string const & kw, 
		    LazySeq<Token> *& tokens,
		    LazyInterp * interp)
    {
      if ( tokens->empty ) {
	stringstream s;
	s << "Unexpected end of input after '" << kw << "'";
	return new LazyErrorForm(s.str());
      }

      Token t = tokens->head;
      if ( t.type != Token::TT_INTEGER ) {
	stringstream s;
	s << "Expected an integer after '" << kw << "', got " << t.contents;
	return new LazyErrorForm(s.str());
      }

      tokens = TokenStream::cdr(tokens);
      if ( tokens->empty ) {
	stringstream s;
	s << "Unexpected end of input after '" << kw << "'";
	return new LazyErrorForm(s.str());
      }

      Token t2 = tokens->head;
      if ( t2.type != Token::TT_KEYWORD ) {
	stringstream s;
	s << "Expected a keyword after '" << kw << " " << t.contents
	  << "', got " << t.contents;
	return new LazyErrorForm(s.str());
      }
      tokens = TokenStream::cdr(tokens);

      int n = atoi(t.contents.c_str());
      stringstream s;
      for ( int i = 0 ; i < n ; ++i ) {
	s << t2.contents << " ";
      }

      TokenStream * newTokenStream = new TokenStream(s.str());
      LazySeqStat::addref(newTokenStream);
      if ( ! newTokenStream->empty ) {
	tokens = new Appender<Token>(newTokenStream, tokens);
      }
      // LazySeqStat::deref(newTokenStream);

      return interp->parse();
    }
  };

  map<string, KwProcessor *> buildKwProcessorMap()
  {
    map<string, KwProcessor *> theMap;

    theMap["append"]     = new StreamStreamMaker<Appender<int> >();
    theMap["count"]      = new StreamMaker<Counter<int> >();
    theMap["drop"]       = new StreamIntMaker<Dropper<int> >();
    theMap["fibonacci"]  = new BasicMaker<Fibonacci>();
    theMap["ghamming"]   = new StreamMaker<GeneralizedHamming>();
    theMap["hamming"]    = new BasicMaker<Hamming>();
    theMap["minmax"]     = new StreamMaker<MinMaxer<int> >();
    theMap["naturals"]   = new BasicMaker<Naturals<int> >();
    theMap["recurse"]    = new RecurseMaker();
    theMap["repeat"]     = new IntMaker<Forever<int> >();
    theMap["take"]       = new StreamIntMaker<Taker<int> >();
    theMap["takewhile"]  = new WhileMaker();
    theMap["whatsit"]    = new StreamMaker<AnonSeq<int> >();
    theMap["while"]      = new WhileMaker();

    return theMap;
  }
}


#define NOT_IMPLEMENTED \
  { \
    return new LazyErrorForm(string(__FUNCTION__) + " is not implemented"); \
  }

LazyInterp::LazyInterp()
  : tokens(NULL)
{
}

LazyInterp::~LazyInterp()
{
  LazySeqStat::deref(tokens);
}


LazyForm * LazyInterp::parse(char const * _spec)
{
  string input(_spec);
  return parse(input);
}

LazyForm * LazyInterp::parse(string & input)
{
  if ( tokens ) {
    delete tokens;
  }
  tokens = new TokenStream(input);
  TRACEALLOC(tokens);
  LazyForm * form = NULL;
  LazySeqStat::addref(tokens);

  if ( tokens->empty ) {
    LazySeq<int> * z = new NullSeq<int>();
    TRACEALLOC(z);
    LazySeqStat::addref(z);
    form = new LazyIntStream(z);
    LazySeqStat::deref(z);
  }
  else {
    form = parse();
  }

  return form;
}

LazyForm * LazyInterp::parse()
{
  if ( ! tokens ) {
    return new LazyErrorForm("No input to parse");
  }

  Token const & t = tokens->head;
  LazyForm * value = NULL;

  switch ( t.type ) {
  case Token::TT_KEYWORD:
    value = processKeyword();
    break;

  case Token::TT_LPAREN:
    value = processSubexpr();
    break;

  case Token::TT_LSQUARE:
    value = processList();
    break;

  case Token::TT_UNKNOWN:
  default:
    {
      stringstream s;
      s << "Unexpected token in input: '" << t.contents << "'";
      value = new LazyErrorForm(s.str());
    }
  }

  return value;
}

LazyForm * LazyInterp::processKeyword()
{
  static map<string, KwProcessor *> kwMap(buildKwProcessorMap());

  Token t = tokens->head;
  string kw = t.contents;
  tokens = TokenStream::cdr(tokens);

  LazyForm * f = NULL;
  map<string, KwProcessor *>::const_iterator iter = kwMap.find(kw);
  if ( iter != kwMap.end() ) {
    f = iter->second->make(kw, tokens, this);
  }
  else {
    stringstream s;
    s << "Unknown keyword: '" << kw << "'";
    f = new LazyErrorForm(s.str());
  }

  return f;
}

LazyForm * LazyInterp::processSubexpr()
{
  LazyExpression ex(tokens);
  LazyForm * f = ex.getResult();
  if ( f ) {
    return f;
  }

  string const & op = ex.getOp();
  if ( op == "*" ) {
    return processTimes(ex);
  }

  stringstream s;
  s << "Operator '" << op << "' is unknown";
  return new LazyErrorForm(s.str());
}

LazyForm * LazyInterp::processTimes(LazyExpression & ex)
{
  vector<Token> const & args = ex.getArgs();
  if ( args.size() != 2 ) {
    stringstream s;
    s << "operator: '*' expected 2 args, got " << args.size();
    return new LazyErrorForm(s.str());
  }

  LazyForm * f;
  LazySeq<int> * s1;
  f = argToStream(args[0], s1);
  if ( f ) {
    return f;
  }
  LazySeq<int> * s2;
  f = argToStream(args[1], s2);
  if ( f ) {
    return f;
  }

  LazySeq<int> * z = new Transformer2<multiplies<int> >(s1, s2);
  TRACEALLOC(z);
  LazySeqStat::addref(z);
  f = new LazyIntStream(z);
  LazySeqStat::deref(z);
  LazySeqStat::deref(s2);
  LazySeqStat::deref(s1);

  return f;
}

LazyForm * LazyInterp::argToStream(Token const & arg, LazySeq<int> *& seq)
{
  if ( arg.type == Token::TT_INTEGER ) {
    int n = atoi(arg.contents.c_str());
    seq = new Forever<int>(n);
    LazySeqStat::addref(seq);
    return NULL;
  }

  if ( arg.type == Token::TT_PLACEHOLDER ) {
    LazyForm * subform = parse();
    LazyIntStream * s = dynamic_cast<LazyIntStream *>(subform);
    if ( ! s ) {
      return subform;
    }
    seq = s->getSequence();
    LazySeqStat::addref(seq);
    delete subform;
    return NULL;
  }

  stringstream s;
  s << "Cannot turn '" << arg.contents << "' into a stream";
  return new LazyErrorForm(s.str());
}

LazyForm * LazyInterp::processList()
{
  vector<int> items;

  while ( true ) {
    tokens = TokenStream::cdr(tokens);
    if ( tokens->empty ) {
      return new LazyErrorForm("Unterminated list, expecting ']'");
    }
    
    Token const & t = tokens->head;
    if ( t.type == Token::TT_INTEGER ) {
      items.push_back(atoi(t.contents.c_str()));
    }
    else if ( t.type == Token::TT_RSQUARE ) {
      LazySeq<int> * z = new List<int>(items);
      TRACEALLOC(z);
      LazySeqStat::addref(z);
      LazyForm * f = new LazyIntStream(z);
      LazySeqStat::deref(z);
      return f;
    }
    else {
      stringstream s;
      s << "Unexpected input in list: '" << t.contents << "'";
      return new LazyErrorForm(s.str());
    }
  }

  stringstream s;
  s << "Internal error at file " << __FILE__ << ", line " << __LINE__;
  return new LazyErrorForm(s.str());
}


