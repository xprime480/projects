#include <iostream>
#include <setjmp.h>

// setjmp fun

jmp_buf env;

struct X
{
  ~X() { std::cout << "Die X\n"; }
};

void b()
{
  longjmp( env, 1 );
}

void a()
{
  X x;				// destructor never called.
  b();
}

int main( int, char ** )
{
  switch ( setjmp( env ) ) {
  case 0:
    std::cout << "starting\n";
    a();
    std::cout << "normal finish\n";
    break;
  default:
    std::cout << "abnormal finish\n";
    break;
  }

  return 0;
}
