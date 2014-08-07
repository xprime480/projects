#if ! defined(ArgParser_h)
#define ArgParser_h 1

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace ArgParser {

  class Argument;
  class ParsedArgs;

  class ArgParserException : public std::runtime_error
  {
  public:
    ArgParserException(std::string const & reason);
  protected:
  private:
  };

  class ArgumentParser
  {
  public:
    ArgumentParser();

    void addArgument(Argument const & arg);

    ParsedArgs parseArgs(int argc, char const ** argv) const;

  protected:
  private:
    std::string remainder;
    std::vector<Argument> args;
  };

  class ArgParserArgCounts
  {
  public:
  protected:
  private:
  };

  static const ArgParserArgCounts OPTIONAL;
  static const ArgParserArgCounts REMAINDER;

  class Argument 
  {
  public:
    Argument(std::string const & label, std::string const & argCount);
    Argument(std::string const & label, ArgParserArgCounts const & argCount);
    
    void setDefault(std::string const & value);
    void setHelp(std::string const & value);

    std::string const & getName() const;

    size_t getArityMin() const;
    size_t getArityMax() const;

  protected:
  private:
    std::string const name;
    size_t arity_min;
    size_t arity_max;
  };

  class ArgValue
  {
  public:
    std::string to_string() const;
    std::vector<std::string> to_string_list() const;
  protected:
  private:
    std::vector<std::string> values;
  };

  class ParsedArgs 
  {
  public:
    ParsedArgs();
    ArgValue const & operator[](std::string const & key) const;
    size_t getArgCount() const;

  protected:

  private:
    friend class ArgumentParser;
    
    void addArgument(std::string name, ArgValue value);
    std::map<std::string, ArgValue> args;
  };

}

#endif
