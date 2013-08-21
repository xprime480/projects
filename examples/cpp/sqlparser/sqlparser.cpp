// $Id: /home/I809989/test/cpp/sqlparser/sqlparser.cpp#1 $
// $DateTime: Wed Nov  9 10:37:04 2011 $

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "FileCharacterStream.h"
#include "StringCharacterStream.h"

#include "SqlTokenStream.h"

#include "AllParsers.h"
#include "SqlParser.h"

using namespace std;
using namespace parser;

namespace {

  void results(Expression const & e)
  {
    if ( e ) {
      cout << "Parse succeeded" << endl;
      cout << e.nth(1) << endl;
    }
    else {
      cout << "Parse failed" << endl;
    }
  }

  void test(Parser & parser, 
	    parser::CharacterStream & data, 
	    int flags = PARSER_FLAGS_TRACE)
  {
    data.reset();
    SqlTokenStream tokens(data);
    cout << "with input " << data.debug() << endl;

    try {
      Expression pr(parser.parse(tokens, flags));
      results(pr);
    }
    catch ( ParserException e ) {
      cout << "Parse threw an exception: " << e.what() << endl;
    }
  }

  bool grabArg(string const & name, string const & spec, string & arg)
  {
    size_t size  = spec.size();
    size_t psize = name.size();
    if ( size >= psize && spec.substr(0,psize) == name ) {
      if ( size < (2 + psize) ) {
	stringstream s;
	s << "no argument specified for parser type " << name;
	throw runtime_error(s.str());
      }
    
      arg = string(spec, 1 + psize);
      return true;
    }

    return false;
  }

  vector<string> split(string const & input, char sep = ',', char esc = '\\')
  {
    string arg;
    size_t len = input.size();
    vector<string> rv;
    bool literal = false;

    for ( size_t i = 0 ; i < len ; ++i ) {
      char ch = input.at(i);

      if ( literal ) {
	arg += ch;
	literal = false;
      }

      if ( ch == esc && sep != esc ) {
	literal = true;
	continue;
      }

      if ( ch == sep ) {
	if ( ! arg.empty() ) {
	  rv.push_back(arg);
	}
	arg = "";
      }
      else {
	arg += ch;
      }
    }

    if ( literal ) {
      throw runtime_error("split: string ends in an escape character");
    }

    if ( ! arg.empty() ) {
      rv.push_back(arg);
    }

    return rv;
  }

  Parser * makeParser(string const & spec)
  {
    string arg;
    size_t size = spec.size();

    if ( size == 0 ) {
      throw runtime_error("no parser type specified");
    }

    if ( spec == "null" ) {
      return new NullParser;
    }    

    if ( grabArg("single", spec, arg) ) {
      return new SingleCharParser(arg.at(0));
    }

    if ( grabArg("anychar", spec, arg) ) {
      return new AnyCharOfParser(arg);
    }

    if ( spec == "lower" ) {
      return new AnyCharOfParser(parser::lowercase);
    }

    if ( spec == "upper" ) {
      return new AnyCharOfParser(parser::uppercase);
    }

    if ( spec == "digits" ) {
      return new AnyCharOfParser(parser::digits);
    }

    if ( spec == "hexdigits" ) {
      return new AnyCharOfParser(parser::hexdigits);
    }

    if ( spec == "whitespace" ) {
      return new AnyCharOfParser(parser::whitespace);
    }

    if ( grabArg("anyof", spec, arg) ) {
      vector<Parser *> parsers;
      vector<string>   parts = split(arg, ';');

      typedef vector<string>::const_iterator iter;
      for ( iter i = parts.begin() ; i != parts.end() ; ++i ) {
	parsers.push_back(makeParser(*i));
      }

      return new AnyOfParser(parsers);
    }

    stringstream s;
    s << "parser spec " << spec << " does not name a supported parser";
    throw runtime_error(s.str());
  }
}

int main(int argc, char ** argv)
{
  if ( argc < 2 || string("--help") == argv[1] ) {
    cerr << "Usage: " << argv[0] << " [--parser=P] input" << endl;
    return 1;
  }

  try {
    SqlParser parser;

    while ( --argc ) {
      string file(*++argv);
      cout << "Beginning test on file " << file << endl;
      FileCharacterStream cs(file);
      test(parser, cs);
    }
  
    return 0;
  }
  catch ( runtime_error e ) {
    cerr << "caught exeption " << e.what() << endl;
  }
    
  return 1;
}
