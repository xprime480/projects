
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

struct Q
{
  int x;
};

struct Z
{
  operator bool() const		// can cast to elementary types
  {
    return x == 0;
  }

  operator Q() const		// can cast to class types
  {
    Q q;
    q.x = x+1;
    return q;
  }

  int x;
};


Z f()
{
  Z z;
  z.x = (getpid() % 2);
  return z;
}

int main(int argc, char ** argv)
{
  if ( f() ) {
    cerr << "yes" << endl;
  }
  else {
    cerr << "no" << endl;
  }

  Q q = f();
  cerr << q.x << endl;
}


