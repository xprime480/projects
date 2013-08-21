// $Id: /home/I809989/test/cpp/parser/Expression.h#1 $
// $DateTime: Mon Apr 18 16:00:18 2011 $

#if ! defined(Expression_h)
#define Expression_h 1

#include <vector>
#include <iosfwd>

namespace parser {
  class Expression;

  class Expression {
  public:
    typedef enum {
      EV_BOOL,
      EV_INT,
      EV_DOUBLE,
      EV_STR,
      EV_LIST
    } tag_type;


    Expression(bool b);
    Expression(int i);
    Expression(double d);
    Expression(char const * c);
    Expression();
    Expression(Expression const & e);
    Expression & operator=(Expression const & e);

    ~Expression();
    
    operator bool() const;
    operator int() const;
    operator double() const;
    operator char const*() const;

    void addText(char const * c);
    void append(Expression const & e);
    size_t size() const;
    Expression const & nth(size_t i) const;
    Expression & nth(size_t i);

    std::ostream & print(std::ostream & os) const;
   
  private:
    typedef std::vector<Expression> vofe;
    tag_type tag;
    union ExprValue {
      bool    b;
      int     i;
      double  d;
      char   *c;
      vofe   *v;
    } value;
  };

  extern Expression nil;
}

std::ostream & operator<<(std::ostream & os, parser::Expression const & e);

#endif // not defined Expression_h
