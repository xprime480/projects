
#include <map>
#include <iostream>
#include <vector>

using namespace std;

struct Point
{
  Point(float _x, float _y) : x(_x), y(_y) {}
  float x,y;
};

void print_headers(char const * const * h)
{
  for ( ; h && *h ; ++h ) {
    cout << *h << " ";
  }
  cout << endl;
}

void debugFormat(map<int, int> const & m, char const * const * h)
{
  typedef map<int, int>::const_iterator iter_type;

  print_headers(h);

  iter_type b = m.begin();
  iter_type e = m.end();
  for ( ; b != e ; ++b ) {
    cout << b->first << " " << b->second << endl;
  }
}

void debugFormat(std::vector<Point>& v, 
		 char const * const * h, 
		 float Point::*pmfx, 
		 float Point::*pmfy)
{
  typedef std::vector<Point>::const_iterator iter_type;

  print_headers(h);
  
  iter_type b = v.begin();
  iter_type e = v.end();
  for ( ; b != e ; ++b ) {
    cout << (*b).*pmfx << " " << (*b).*pmfy << endl;
  }
  
}

void test1()
{
  char const * hdrs[] = { "N", "Val", 0 };

  std::map<int, int> m;
  m[1] = 2;
  m[3] = 7;

  debugFormat(m, hdrs);
}

void test2()
{
  char const * hdrs[] = { "X", "Y", 0 };

  vector<Point> vp;
  vp.push_back(Point(1.23, 4.56));
  vp.push_back(Point(7.00, 0.01));

  debugFormat(vp, hdrs, &Point::x, &Point::y);
}

int main(int argc, char ** argv)
{
  test1();
  test2();

#if 0
  HeaderBuilder hdr;

  int i = 0;
  hdr.addValue<int>("Test");
  debugFormat(i, hdr.header());

  std::map<int, int> m;
  m[1] = 2;
  m[3] = 7;
  hdr.reset();
  hdr.addKey("N");
  hdr.addValue<int>("Val");
  debugFormat(m, hdr.header());

  std::set<int> s;
  s.insert(7);
  s.insert(-134);
  hdr.reset();
  hdr.addValue<int>("Set Val");
  debugFormat(s, hdr.header());

  std::vector<int> vi(s.begin(), s.end());
  hdr.reset();
  hdr.addValue<int>("Vec Val");
  debugFormat(vi, hdr.header());

  hdr.reset();
  hdr.addValue<Point>("X;Y");
  debugFormat(vp, hdr.header());
#endif

  return 0;
}
