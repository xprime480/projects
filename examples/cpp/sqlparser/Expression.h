// $Id: /home/I809989/test/cpp/parser/Expression.h#1 $
// $DateTime: Mon Apr 18 16:00:18 2011 $

#if ! defined(Expression_h)
#define Expression_h 1

#include <vector>

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


    explicit Expression(bool b);
    explicit Expression(int i);
    explicit Expression(double d);
    explicit Expression(char const * c);
    Expression();
    explicit Expression(Expression const & e);
    Expression & operator=(Expression const & e);

    ~Expression();

    operator bool() const;
    operator int() const;
    operator double() const;
    operator char*() const;

    void append(Expression const & e);
    size_t size() const;
    Expression const & nth(size_t i);
   
  private:
    typedef std::vector<Expression> vofe;
    tag_type tag;
    union {
      bool    b;
      int     i;
      double  d;
      char   *c;
      vofe   *v;
    } value;
  };

  extern Expression nil;
}

#endif // not defined Expression_h
