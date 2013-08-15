
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

bool isFlag(string const & str)
{
  return str.size() >= 2 && str.at(0) == '-' && str.at(1) == '-';
}

int main(int argc, char ** argv)
{
  vector<string> args;
  copy(argv+1, argv+argc, back_inserter(args));
  copy(args.begin(), args.end(), ostream_iterator<string>(cout, "\n"));
  cout << "----------" << endl;
  ptrdiff_t flags = count_if(args.begin(), args.end(), isFlag);
  cout << args.size() << " inputs" << endl;
  cout << flags << " flags" << endl;
  cout << "----------" << endl;
}
