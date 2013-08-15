
#include <iostream>
#include <iomanip>

struct BarBase
{
  virtual ~BarBase()
  {
  }

  virtual std::ostream & operator()(std::ostream & t) const = 0;
};

struct Bar : public BarBase
{
  Bar(int w, int p)
    : width(w)
    , precision(p)
  {
  }

  std::ostream & operator()(std::ostream & t) const
  {
    t << std::scientific
      << std::setw(width)
      << std::right 
      << std::setprecision(precision);
    return t;
  }

private:
  int width;
  int precision;
};

Bar bar(int w, int p)
{
  return Bar(w,p);
}

std::ostream & operator<<(std::ostream & t, BarBase const & b)
{
  b(t);
  return t;
}

std::ostream & foo(std::ostream & t)
{
  t << std::scientific
    << std::setw(30)
    << std::right 
    << std::setprecision(3);
  return t;
}

int main(int, char **)
{
  double d = 1.23456789e-8;
  std::ios_base::fmtflags flags = std::cout.flags();

  std::cout << std::boolalpha << true << " or " << false << std::endl;

  std::cout << std::hex << std::showbase << 16 << std::endl;
  std::cout << std::oct << std::showbase << 16 << std::endl;
  std::cout << std::dec << std::showbase << 16 << std::endl;

  std::cout << std::fixed      << d << std::endl;
  std::cout << std::scientific << d << std::endl;

  std::cout << foo << d << std::endl;
  std::cout << bar(20,6) << d << std::endl;

  std::cout.flags(flags);

  std::cout << d << std::endl;

  return 0;
}
