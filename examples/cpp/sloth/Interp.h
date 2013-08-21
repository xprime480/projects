#if ! defined(Lazy_Interp_h)
#define Lazy_Interp_h 1

#include <deque>
#include <map>
#include <string>
#include <vector>

#include "debug.h"
#include "Form.h"
#include "Tokenizer.h"

namespace Sloth
{
  /**
   * LazyInterp
   *
   * Interpreter for the Sloth language.
   * 
   * Examples:
   *
   * If the sequence is not empty, then head holds M, tail()->head holds
   * V, and tail()->tail() lazily computes the remainder of the sequence.
   */
  class Interp
  {
  public:
    /**
     * constructor
     */
    Interp();

    /**
     * destructor
     */
    ~Interp();

    /**
     * parse
     *
     * turn character input into an internal stack
     *
     * @param _spec the input
     *
     * @return result of parsing, either a sequence or an error
     *         message.
     */
    void parse(char const * _spec);

    /**
     * parse
     *
     * turn character input into an internal stack
     *
     * @param _spec the input
     *
     * @return result of parsing, either a sequence or an error
     *         message.
     */
    void parse(std::string & input);

    /**
     * parse
     *
     * turn internal token stream into an internal stack
     *
     * @param _spec the input
     *
     * @return result of parsing, either a sequence or an error
     *         message.
     */
    void parse();

    void printTop();

  private:
    Tokenizer tokens;

    std::deque<Form> evalStack;	// internal stack

    void parseOne();

    /**
     * processKeyword
     * 
     * process input that looks like a keyword name
     *
     * @return an error message or a lazy sequence form
     */
    void processKeyword(std::string const & op);

    /**
     * processSubexpr
     * 
     * process input that looks like a subexpression e.g. (* 2 3)
     *
     * @return an error message or a lazy sequence form
     */
    void processSubexpr(std::string const & op);

    /**
     * processList
     * 
     * process input that looks like a number list e.g. [1 2 3]
     *
     * @return an error message or a lazy sequence form
     */
    void processList(std::string const & op);	// process [1 2 ...]

    std::map<std::string, void (Interp::*)(std::string const &)>
    buildKwProcessorMap();

    void v2s(std::string const & kw);

    void i2s(std::string const & kw);

    void ii2s(std::string const & kw);

    void s2s(std::string const & kw);

    void ss2s(std::string const & kw);

    void si2s(std::string const & kw);

    void s2i(std::string const & kw);

    void pop(std::string const & kw);

    void print(std::string const & kw);

    void printAll(std::string const & kw = "printall");

    void printMessages();

    void dup(std::string const & kw);

    void eval(std::string const & kw);

    void swap(std::string const & kw);

    void binop(std::string const & kw);

    void unop(std::string const & kw);

    void dumpStack(std::string const & msg);

    bool expects(std::string const & kw, size_t count);

    bool grab(std::string const & kw, size_t count, int & value);

    bool grab(std::string const & kw, size_t count, Form & value);
  };

}

#endif // not defined Lazy_Interp_h
