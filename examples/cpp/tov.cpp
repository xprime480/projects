
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <typename T, typename U>
struct Converter
{
  U convert(T const & t)
  {
    return U(t);
  }
};

template <typename T>
struct Converter<T, T>
{
  T convert(T const & t)
  {
    return t;
  }
};

template <typename T>
struct Converter<T, string>
{
  string convert(T const & t)
  {
    stringstream s;
    s << "<";
    s << t;
    s << ">";
    return s.str();
  }
};


main(int argc, char ** argv)
{
  Converter<char, char> ccc;
  cout << ccc.convert('z') << endl;

  Converter<unsigned int, char> uicc;
  cout << uicc.convert(1045) << endl;

  Converter<char, unsigned int> cuic;
  cout << cuic.convert('z') << endl;
  
  Converter<unsigned int, string> uisc;
  cout << uisc.convert(10234) << endl;
  
  return 0;
}
