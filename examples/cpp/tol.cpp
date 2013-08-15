/**
 * Remind myself of how the using declaration works with regard to
 * partially overridden member functions.
 */

#include <iostream>
#include <string>

using namespace std;

struct A
{
  virtual void M(int)
  {
    cerr << __LINE__ << endl;
  };

  virtual void M(string &)
  {
    cerr << __LINE__ << endl;
  }
};

struct B : public A
{
  using A::M;

  virtual void M(int)
  {
    cerr << __LINE__ << endl;
  };

};

void f(A & a)
{
  string x;
  a.M(2);
  a.M(x);
}


int main(int argc, char ** argv)
{
  A a;
  B b;

  f(a);
  f(b);

  string x;

  a.M(1);
  a.M(x);
  
  b.M(1);
  b.M(x);
}
