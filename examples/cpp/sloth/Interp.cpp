
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>

#include "Generators.h"
#include "FormFactory.h"
#include "Tokenizer.h"
#include "Utils.h"

#include "Interp.h"

using namespace std;
using namespace Sloth;

Interp::Interp()
{
}

Interp::~Interp()
{
}

void Interp::parse(char const * _spec)
{
  string input(_spec);
  parse(input);
}

void Interp::parse(string & input)
{
  // cerr << "Entering parser with input: '" << input << "'" << endl;

  tokens.tokenize(input);
  parse();
  // cerr << "Returning from parser with value: '" << f.toString() << "'" << endl;
}

void Interp::parse()
{
  dumpStack("entering parser");

  while ( ! tokens.empty() ) {
    parseOne();
  }

  printMessages();
  dumpStack("processed all tokens");
}

void Interp::parseOne()
{
  printMessages();

  Token t = tokens.front();
  dumpStack(string("Token: '") + t.contents + "'");
  tokens.next();

  switch ( t.type ) {
  case Token::TT_KEYWORD:
  case Token::TT_OPERATOR:
    processKeyword(t.contents);
    break;

  case Token::TT_LSQUARE:
    processList(t.contents);
    break;

  case Token::TT_INTEGER:
    {
      Form f = FormFactory::makeInt(atoi(t.contents.c_str()));
      evalStack.push_front(f);
    }
    break;

  case Token::TT_STRING:
    {
      Form f = FormFactory::makeString(t.contents.c_str());
      evalStack.push_front(f);
    }
    break;

  case Token::TT_SYMBOL:
    {
      Form f = FormFactory::makeSymbol(t.contents.c_str());
      evalStack.push_front(f);
    }
    break;

  case Token::TT_BOOLEAN:
    {
      char const c = t.contents.c_str()[1];
      Form f = FormFactory::makeBoolean(c == 't' || c == 'T');
      evalStack.push_front(f);
    }
    break;

  case Token::TT_UNKNOWN:
  default:
    {
      stringstream s;
      s << "Unexpected token in input: '" << t.contents << "'";
      Form f = FormFactory::makeMessage(s.str());
      evalStack.push_front(f);
    }
    break;
  }
}

map<string, void (Interp::*)(string const &)> Interp::buildKwProcessorMap()
{
  map<string, void (Interp::*)(string const &)> theMap;

  /** stream making primitives */

  theMap["append"]     = &Interp::ss2s;
  theMap["drop"]       = &Interp::si2s;
  theMap["fibonacci"]  = &Interp::v2s;
  theMap["flatten"]    = &Interp::s2s;
  theMap["gfibonacci"] = &Interp::ii2s;
  theMap["minmax"]     = &Interp::s2s;
  theMap["naturals"]   = &Interp::v2s;
  theMap["repeat"]     = &Interp::i2s;
  theMap["set"]        = &Interp::ss2s;
  theMap["take"]       = &Interp::si2s;
  theMap["takeif"]     = &Interp::ss2s;

  /** integer making primitives */

  theMap["count"]      = &Interp::s2i;

#if 0
  theMap["ghamming"]   = new StreamMaker<GeneralizedHamming>();
  theMap["hamming"]    = new BasicMaker<Hamming>();
  theMap["recurse"]    = new RecurseMaker();
  theMap["takewhile"]  = new WhileMaker();
  theMap["whatsit"]    = new StreamMaker<AnonSeq<int> >();
  theMap["while"]      = &Interp::ss2s;
#endif

  /** stack manipulation primitives **/

  theMap["dup"]      = &Interp::dup;
  theMap["eval"]     = &Interp::eval;
  theMap["pop"]      = &Interp::pop;
  theMap["print"]    = &Interp::print;
  theMap["printall"] = &Interp::printAll;
  theMap["swap"]     = &Interp::swap;

  /** operators **/

  static set<string> binops(BinopGenerator::getBinopSet());
  set<string>::const_iterator iter;
  for ( iter = binops.begin() ; iter != binops.end() ; ++iter ) {
    theMap[*iter] = &Interp::binop;
  }

  static set<string> unops(UnopGenerator::getUnopSet());
  // set<string>::const_iterator iter;
  for ( iter = unops.begin() ; iter != unops.end() ; ++iter ) {
    theMap[*iter] = &Interp::unop;
  }

  /** done **/

  return theMap;
}

void Interp::processKeyword(string const & op)
{
  static map<string, void (Interp::*)(string const &)>
    opMap(buildKwProcessorMap());

  map<string, void (Interp::*)(string const &)>::const_iterator iter;
  iter = opMap.find(op);
  if ( iter != opMap.end() ) {
    void (Interp::*pfn)(string const &) = iter->second;
    (this->*pfn)(op);
  }
  else {
    stringstream s;
    s << "Unknown keyword: '" << op << "'";
    Form f = FormFactory::makeMessage(s.str());
    evalStack.push_front(f);
  }
}

void Interp::processList(string const & op)
{
  static string const sentinelMessage = "ListSentinel";
  Form sentinel = FormFactory::makeString(sentinelMessage);
  evalStack.push_front(sentinel);

  while ( true ) {
    if ( tokens.empty() ) {
      Form f = FormFactory::makeMessage("Unterminated list, expecting ']'");
      evalStack.push_front(f);
      break;
    }

    Token const & t = tokens.front();
    if ( t.type == Token::TT_RSQUARE ) {
      tokens.next();
      vector<Form> values;
      Form f;
      size_t n = 1;
      while ( grab(op, n++, f) ) {
	if ( f.hasStringValue() &&
	     f.getStringValue() == sentinelMessage ) {
	  Form x = FormFactory::makeSequence(new ListGenerator(values));
	  evalStack.push_front(x);
	  break;
	}
	else {
	  values.insert(values.begin(), f);
	}
      }
      break;
    }
    else {
      parseOne();
    }
  }
}

void Interp::v2s(string const & kw)
{
  Form x;
  if ( kw == "naturals" ) {
    x = FormFactory::makeSequence(new SliceGenerator(1,
						     numeric_limits<int>::max(),
						     1));
  }
  else if ( kw == "fibonacci" ) {
    x = FormFactory::makeSequence(new FibonacciGenerator());
  }
  else {
    stringstream s;
    s << "Interp::v2s: unknown keyword: " << kw;
    x = FormFactory::makeMessage(s.str());
  }

  evalStack.push_front(x);
}

void Interp::i2s(string const & kw)
{
  if ( ! expects(kw, 1) ) {
    return;
  }

  int i1;
  if ( ! grab(kw, 1, i1) ) {
    return;
  }

  Form x;
  if ( kw == "repeat" ) {
    Form i = FormFactory::makeInt(i1);
    x = FormFactory::makeSequence(new Infinite(i));
  }
  else {
    stringstream s;
    s << "Interp::ii2s: unknown keyword: " << kw;
    x = FormFactory::makeMessage(s.str());
  }

  evalStack.push_front(x);
}

void Interp::ii2s(string const & kw)
{
  if ( ! expects(kw, 2) ) {
    return;
  }
  int i1;
  if ( ! grab(kw, 1, i1) ) {
    return;
  }

  int i2;
  if ( ! grab(kw, 2, i2) ) {
    return;
  }

  Form x;
  if ( kw == "gfibonacci" ) {
    x = FormFactory::makeSequence(new GeneralizedFibonacciGenerator(i2, i1));
  }
  else {
    stringstream s;
    s << "Interp::ii2s: unknown keyword: " << kw;
    x = FormFactory::makeMessage(s.str());
  }

  evalStack.push_front(x);
}

void Interp::s2s(string const & kw)
{
  if ( ! expects(kw, 1) ) {
    return;
  }

  Form q1;
  if ( ! grab(kw, 1, q1) ) {
    return;
  }

  Form x;
  if ( kw == "minmax" ) {
    x = FormFactory::makeSequence(new MinMaxGenerator(q1));
  }
  else if ( kw == "flatten" ) {
    x = FormFactory::makeSequence(new FlattenGenerator(q1));
  }
  else {
    stringstream s;
    s << "Interp::s2s: unknown keyword: " << kw;
    x = FormFactory::makeMessage(s.str());
  }

  evalStack.push_front(x);
}

void Interp::ss2s(string const & kw)
{
  if ( ! expects(kw, 2) ) {
    return;
  }

  Form q1;
  if ( ! grab(kw, 1, q1) ) {
    return;
  }

  Form q2;
  if ( ! grab(kw, 2, q2) ) {
    return;
  }

  Form x;
  if ( kw == "append" ) {
    x = FormFactory::makeSequence(new Appender(q2, q1));
  }
  else if ( kw == "takeif" ) {
    x = FormFactory::makeSequence(new TakeIfGenerator(q1, q2));
  }
  else if ( kw == "set" ) {
    x = q2.setValue(q1);
  }
  else {
    stringstream s;
    s << "Interp::s2s: unknown keyword: " << kw;
    x = FormFactory::makeMessage(s.str());
  }

  evalStack.push_front(x);
}

void Interp::si2s(string const & kw)
{
  if ( ! expects(kw, 2) ) {
    return;
  }
  int i1;
  if ( ! grab(kw, 1, i1) ) {
    return;
  }

  Form q2;
  if ( ! grab(kw, 2, q2) ) {
    return;
  }

  Form x;
  if ( kw == "take" ) {
    x = FormFactory::makeSequence(new TakeGenerator(q2, i1));
  }
  else if ( kw == "drop" ) {
    x = FormFactory::makeSequence(new DropGenerator(q2, i1));
  }
  else {
    stringstream s;
    s << "Interp::si2s: unknown keyword: " << kw;
    x = FormFactory::makeMessage(s.str());
  }

  evalStack.push_front(x);
}

void Interp::s2i(string const & kw)
{
  if ( ! expects(kw, 1) ) {
    return;
  }

  Form q1;
  if ( ! grab(kw, 1, q1) ) {
    return;
  }

  Form x;
  if ( kw == "count" ) {
    x = FormFactory::makeInt(new CountGenerator(q1));
  }
  else {
    stringstream s;
    s << "Interp::s2i: unknown keyword: " << kw;
    x = FormFactory::makeMessage(s.str());
  }

  evalStack.push_front(x);
}


void Interp::pop(string const & kw)
{
  if ( ! expects(kw, 1) ) {
    return;
  }
  Form q1;
  if ( ! grab(kw, 1, q1) ) {
    return;
  }
}

void Interp::print(string const & kw)
{
  if ( ! expects(kw, 1) ) {
    return;
  }
  Form q1;
  if ( ! grab(kw, 1, q1) ) {
    return;
  }

  cout << q1 << endl;
}

void Interp::printAll(string const & kw)
{
  while ( ! evalStack.empty() ) {
    print(kw);
  }
}

void Interp::printMessages()
{
  while ( ! evalStack.empty() ) {
    if ( evalStack.front().isMessage() ) {
      print("printMessages");
    }
    else {
      break;
    }
  }
}

void Interp::dup(string const & kw)
{
  if ( ! expects(kw, 1) ) {
    return;
  }
  Form q1;
  if ( ! grab(kw, 1, q1) ) {
    return;
  }

  evalStack.push_front(q1);
  evalStack.push_front(q1);
}

void Interp::eval(string const & kw)
{
  if ( ! expects(kw, 1) ) {
    return;
  }
  Form q1;
  if ( ! grab(kw, 1, q1) ) {
    return;
  }


  EVAL_START_1(q1);
  Form r1 = q1.eval();
  EVAL_FINISH(r1);
  evalStack.push_front(r1);
}

void Interp::swap(string const & kw)
{
  if ( ! expects(kw, 2) ) {
    return;
  }
  Form q1;
  if ( ! grab(kw, 1, q1) ) {
    return;
  }

  Form q2;
  if ( ! grab(kw, 2, q2) ) {
    return;
  }

  evalStack.push_front(q1);
  evalStack.push_front(q2);
}

void Interp::binop(string const & kw)
{
  dumpStack("Entering");

  if ( ! expects(kw, 2) ) {
    return;
  }

  Form q1;
  if ( ! grab(kw, 1, q1) ) {
    return;
  }

  Form q2;
  if ( ! grab(kw, 2, q2) ) {
    return;
  }

  Form f;
  f = FormFactory::makeSequence(new BinopGenerator(kw, q2, q1));
  evalStack.push_front(f);
}

void Interp::unop(string const & kw)
{
  dumpStack("Entering");

  if ( ! expects(kw, 1) ) {
    return;
  }

  Form q1;
  if ( ! grab(kw, 1, q1) ) {
    return;
  }

  Form f;
  f = FormFactory::makeSequence(new UnopGenerator(kw, q1));
  evalStack.push_front(f);
}

void Interp::dumpStack(string const & msg)
{
  return;
  cerr << endl;
  cerr << msg << endl;
  cerr << "-------- stack ---------" << endl;
  deque<Form>::const_iterator iter;
  for ( iter = evalStack.begin() ; iter != evalStack.end() ; ++iter ) {
    cerr << iter->toString() << endl;
  }
  cerr << "------ end stack -------" << endl;
  cerr << endl;
}

bool Interp::expects(string const & kw, size_t count)
{
  if ( evalStack.size() < count ) {
    stringstream s;
    s << "'" << kw << "' expects " << count
      << " arguments; got " << evalStack.size();

    Form f = FormFactory::makeMessage(s.str());
    evalStack.push_front(f);
    return false;
  }

  return true;
}

bool Interp::grab(string const & kw, size_t count, int & value)
{
  bool rv = false;

  Form arg = evalStack.front();
  if ( arg.hasIntValue() ) {
    value = arg.getIntValue();
    evalStack.pop_front();
    rv = true;
  }
  else {
    stringstream s;
    s << "'" << kw << "' expects an integer argument in position "
      << count << "; got '" << arg.toString() << "'";
    Form f = FormFactory::makeMessage(s.str());
    evalStack.push_front(f);
    rv = false;
  }

  return rv;
}

bool Interp::grab(string const & kw, size_t count, Form & value)
{
  if ( evalStack.empty() ) {
    return false;
  }

  value = evalStack.front();
  evalStack.pop_front();
  return true;
}
