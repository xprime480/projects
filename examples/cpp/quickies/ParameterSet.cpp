// $Id: /home/I809989/test/cpp/ParameterSet.cpp#1 $
// $DateTime: Tue Apr 12 11:01:00 2011 $

#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <sstream>

#include "ParameterSet.h"

using namespace std;


Parameters::Parameters(ParameterSet const & ps)
  : names(ps)
  , values(ps.count())
{
}

void Parameters::set(std::string const & name, double value)
{
  values[names.index(name)] = value;
}

double /*&*/ Parameters::get(std::string const & name)
{
  return values[names.index(name)];
}

//////////////////////////////////////////////////////////

ParameterSet::ParameterSet()
  : locked(false)
{
}

bool ParameterSet::append(string const & name)
{
  if ( locked ) {
    return false;
  }

  iter it = find(name);
  if ( it == end() ) {
    parms.push_back(name);
    return true;
  }

  return false;
}

size_t ParameterSet::index(string const & name) const
{
  iter it = find(name);
  if ( it == end() ) {
    stringstream s;
    s << "parameter " << name << " not present";
    throw runtime_error(s.str());
  }

  return distance(begin(), it);
}

size_t ParameterSet::count() const
{
  return parms.size();
}

string ParameterSet::at(size_t pos) const
{
  return parms.at(pos);
}

Parameters ParameterSet::instance()
{
  locked = true;
  return Parameters(*this);
}

ParameterSet::iter ParameterSet::find(string const & name) const
{
  return std::find(begin(), end(), name);
}

ParameterSet::iter ParameterSet::begin() const
{
  return parms.begin();
}

ParameterSet::iter ParameterSet::end() const
{
  return parms.end();
}

int main(int, char **)
{
  char const * p1[] = { "first", "second", "third" };
  ParameterSet m;
  cout << boolalpha << m.append(p1[0]) << endl;
  cout << boolalpha << m.append(p1[1]) << endl;
  cout << boolalpha << m.append(p1[0]) << endl;

  cout << m.index(p1[0]) << endl;
  cout << m.index(p1[1]) << endl;

  cout << m.at(0) << endl;
  cout << m.at(1) << endl;

  cout << m.count() << endl;
  Parameters mp = m.instance();
  mp.set(p1[0], 2.5);
  cout << mp.get(p1[0]) << endl;

  bool t = m.append(p1[2]);
  cout << boolalpha << t << endl; 
  if ( t ) {
    m.index(p1[2]);
  }

  cout << string(40, '-') << endl;

  char const * p2[] = { "a", "a", "b", "c" };
  ParameterSet q(p2, p2 + 4);
  cout << q.count() << endl;

  return 0;
}
