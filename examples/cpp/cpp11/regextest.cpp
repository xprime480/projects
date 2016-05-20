
#include <regex>
#include <string>
#include <iostream>

using std::string;
using std::regex;
using std::regex_search;
using std::regex_match;
using std::smatch;
using std::cout;
using std::endl;
using std::boolalpha;


void test1()
{
  using std::regex_constants::icase;
  using std::regex_constants::ECMAScript;

  //  const string test_data { "This is some random text" };
  const string test_data { "random" };
  regex  regex1 ( "random", ECMAScript | icase );

  cout << boolalpha;

  smatch m;
  auto sm = regex_search( test_data, m, regex1 );
  cout << sm << endl;
  if ( sm ) {
    cout << "\"search\" matched" << endl;
  }

  auto  mm = regex_match( test_data, regex1 );
  cout << mm << endl;
  if ( mm ) {
    cout << "\"match\" matched" << endl;
  }
}

void regextest(int argc, char ** argv)
{
  test1();
}
