#include <algorithm>
#include <sstream>

#include "ArgParser.h"

using namespace std;
using namespace ArgParser;

ArgParser::ArgParserException::ArgParserException(std::string const & reason)
  : runtime_error(reason)
{
}

ArgParser::ArgumentParser::ArgumentParser()
  : remainder("__NONE__")
{
}

void ArgParser::ArgumentParser::addArgument(Argument const & arg)
{
  struct MatchName
  {
    MatchName(string const & _name)
      : name(_name)
    {
    }

    bool operator()(Argument const & arg)
    {
      return arg.getName() == name;
    }
  private:
    string name;
  };
  auto found = for_each(args.begin(), args.end(), MatchName(arg.getName()));

  if ( false ) {
  }

  args.push_back(arg);
}

ArgParser::ParsedArgs
ArgParser::ArgumentParser::parseArgs(int argc, char const ** argv) const
{
  ParsedArgs rv;

  /*
   * Add default values and remainder arguments.
   */
  typedef vector<Argument>::const_iterator iter_type;
  for ( iter_type iter = args.begin() ; iter != args.end() ; ++iter ) {
    Argument const & arg = *iter;
    if ( 0 == arg.getArityMin() ) {
      ArgValue arg_val;
      rv.addArgument(arg.getName(), arg_val);
    }
  }

  if ( argc ) {
    stringstream s;
    s << "ArgumentParser::parseArgs: excess command line arguments: ";
    for ( int i = 0 ; i < argc ; ++i ) {
      s << argv[i] << " ";
    }
    throw ArgParserException(s.str());
  }
  return rv;
}

const ArgParser::ArgParserArgCounts OPTIONAL;
const ArgParser::ArgParserArgCounts REMAINDER;

namespace {
  string stripPrefix(std::string const & s)
  {
    if ( s.length() > 2 && s.substr(0, 2) == "--" ) {
      return s.substr(2);
    }
    return s;
  }
}

ArgParser::Argument::Argument(string const & label, 
			      ArgParserArgCounts const & argCount)
  : name(label)
  , arity_min(0)
  , arity_max(0)
{
  if ( &REMAINDER == &argCount ) {
    arity_min = 0;
    arity_max = -1;
  }
  else if ( &OPTIONAL == &argCount ) {
    arity_max = 1;
  }
}
    
void ArgParser::Argument::setDefault(string const & value)
{
}

void ArgParser::Argument::setHelp(string const & value)
{
}

string const & ArgParser::Argument::getName() const
{
  return name;
}

size_t ArgParser::Argument::getArityMin() const
{
  return arity_min;
}

size_t ArgParser::Argument::getArityMax() const
{
  return arity_max;
}

string ArgParser::ArgValue::to_string() const
{
  return "";
}

vector<string> ArgParser::ArgValue::to_string_list() const
{
  vector<string> v;
  return v;
}

ArgParser::ParsedArgs::ParsedArgs() 
{
}

ArgValue const & ArgParser::ParsedArgs::operator[](string const & key) const
{
  static ArgValue rv;
  return rv;
}

size_t ArgParser::ParsedArgs::getArgCount() const
{
  return args.size();
}

void ArgParser::ParsedArgs::addArgument(std::string name, ArgValue value)
{
  args[name] = value;
}
