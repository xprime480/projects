
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

#include "ArgParser.h"

using namespace std;

using namespace ArgParser;

namespace {
  class TestException : public runtime_error 
  {
  public:
    TestException(string const & cause)
      : runtime_error(cause)
    {
    }
  };

  void addRemainderArgument(ArgumentParser & parser, string const & name)
  {
    Argument foo(name, REMAINDER);
    foo.setHelp("read all remaining args from command line");
    parser.addArgument(foo);
  }

  
  ParsedArgs sendInput(ArgumentParser const & parser, char const ** argv)
  {
    int argc = 0;
    char const ** ppch = argv;
    while ( *ppch++ ) {
      ++argc;
    }
    return parser.parseArgs(argc, argv);
  }

  void assertArgCount(ParsedArgs const & args, size_t num, string const & tag)
  {
    size_t count = args.getArgCount();
    if ( num != count ) {
      stringstream s;
      s << tag << ": excpected " << num << " parsed args, got: " << count;
      throw TestException(s.str());
    }
  }

  void assertValVector(ArgValue const & arg, 
		       size_t num, 
		       string const & tag)
  {
    vector<string> vals = arg.to_string_list();
    size_t count = vals.size();
    if ( num != count ) {
      stringstream s;
      s << tag << ": excpected " << num << " values, got: " << count;
      throw TestException(s.str());
    }
    copy(vals.begin(), vals.end(), ostream_iterator<string>(cerr, ";"));
  }

  char const * commandLineEmpty[] = { 0 };
  char const * commandLineFoo[] = { "foo", 0 };
  char const * commandLineFourArgs[] = { "one", "too", "3", "fore", 0 };

  void test1()
  {
    /** 
     * test the null parser on a null command line 
     *
     * It is expected to succeed with 0 args parsed.
     */

    ArgumentParser parser;
    ParsedArgs args = sendInput(parser, commandLineEmpty);
    assertArgCount(args, 0, "test1");
  }

  void test2()
  {
    /** 
     * test the null parser on a non-null command line.
     *
     * It is expected to fail to parse with excess command line arguments.
     */

    ArgumentParser parser;
    try {
      (void) sendInput(parser, commandLineFoo);
      throw TestException("test2: expected exception was not thrown");
    }
    catch ( ArgParserException & e ) {
    }
  }

  void test3()
  {
    /**
     * test the argument parser with a single arg that takes all of
     * the command line, tested with no input.
     *
     * It should succeed with one arg and the arg value is an empty
     * vector of strings.
     */

    ArgumentParser parser;
    addRemainderArgument(parser, "foo");
    ParsedArgs args = sendInput(parser, commandLineEmpty);
    assertArgCount(args, 1, "test3");
    ArgValue const & foo = args["foo"];
    assertValVector(foo, 0, "test3");
  }

  void test4()
  {
    /**
     * test the argument parser with a single arg that takes all of
     * the command line, tested with several input args.
     *
     * It should succeed with one arg and the arg value equals the
     * inputs. 
     */

    ArgumentParser parser;
    addRemainderArgument(parser, "foo");
    ParsedArgs args = sendInput(parser, commandLineFourArgs);
    assertArgCount(args, 1, "test4");
    ArgValue const & foo = args["foo"];
    assertValVector(foo, 4, "test4");
  }

  void (*testfns[])() = {
    test1,
    test2,
    test3,
    test4,
    0
  };


}

int main(int argc, char ** argv)
{
  for ( size_t findex = 0 ; testfns[findex] ; ++findex ) {
    try {
      testfns[findex]();
    }
    catch ( exception & e ) {
      cerr << e.what() << endl;
      return 1;
    }
    catch ( ... ) {
      cerr << "Unexpected exception for function number << " << findex << endl;
    }
  }
  return 0;
}
