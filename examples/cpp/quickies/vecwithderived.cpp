#include <iostream>
#include <vector>

class B
{
public:
  virtual ~B() {}
  virtual int get() const = 0;
};

class D1 : public B
{
public:
  virtual int get() const 
  {
    return 42;
  }
};

class D2 : public B
{
public:
  D2(int _v)
    : v(_v)
  {
  }

  virtual int get() const
  {
    return v;
  }

private:
  char data[1024*10];
  int const v;
};

using namespace std;

int main(int argc, char ** argv)
{
  vector<B const *> vb;
  D1 d1;
  D2 d2(3);
  vb.push_back(&d1);
  vb.push_back(&d2);

  cout << vb.at(0)->get() << endl;
  cout << vb.at(1)->get() << endl;

  return 0;
}
