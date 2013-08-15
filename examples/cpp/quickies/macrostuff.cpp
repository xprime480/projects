
#include <iostream>
#include <cstring>

using namespace std;

struct something
{
  char const * str;
  unsigned     sz;
};

char     const * FOO    = "FOO";
unsigned const   FOO_SZ = strlen( FOO );

#define SOME_ENTRY( name ) { #name, name ## _SZ }

something sss[] = { SOME_ENTRY( FOO ) };



int main(int, char **)
{
  std::cerr << sss[0].str << " " << sss[0].sz << "\n";
}
