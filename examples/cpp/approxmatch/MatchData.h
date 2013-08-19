#if ! defined(MatchData_h)
#define MatchData_h 1

#include <cstdlib>
#include <iosfwd>

struct PartialMatchData
{
  PartialMatchData(size_t _score = 0, 
		   size_t _pos   = 0,
		   bool   _inTranspose = false,
		   char   _transposeChar = ' ');

  size_t score;
  size_t pos;
  bool   inTranspose;
  char   transposeChar;
};

struct MatchData
{
  size_t score;
  char const * key;
  size_t value;
};

extern std::ostream & operator<<(std::ostream & os, MatchData const & m);

#endif // not defined MatchData_h
