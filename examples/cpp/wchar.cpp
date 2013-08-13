

#include <iostream>
#include <string>

using namespace std;

int main(int, char **)
{
  wstring test(L"abc");
  wcout << test << endl;
  wcout << sizeof ( wchar_t ) << endl;
}
