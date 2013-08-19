
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "DistanceWithTranspose.h"

using namespace std;

DistanceWithTranspose::DistanceWithTranspose(char const * _s, char const * _t)
  : s(_s)
  , t(_t)
  , lenS(s ? strlen(s) : 0)
  , lenT(t ? strlen(t) : 0)
  , computed(false)
  , val(0)
  , inserts(0)
  , best(lenS + lenT + 1)
{
  if ( 0 == lenS ) {
    val = lenT;
    computed = true;
  }
  else if ( 0 == lenT ) {
    val = lenS;
    computed = true;
  }
}

size_t DistanceWithTranspose::distance()
{
  if ( ! computed ) {
    init_scores();
    compute();
    clear();

    computed = true;
  }

  cout << inserts << " total insertions" << endl;
  return val;
}

void DistanceWithTranspose::init_scores()
{
  Score first(0, 0, 0);
  insert(first);
}

void DistanceWithTranspose::compute() 
{
  while ( ! empty() ) {
    Score & current = get();

    size_t lenSx = current.getOffset1();
    size_t lenTx = current.getOffset2();

    if ( lenS == lenSx && lenT == lenTx ) {
      val = current.getScore(); // this is the best score
      return;
    }

    if ( lenS == lenSx || lenT == lenTx ) {
      throw runtime_error("should never have to test a null string");
    }

    char chS0 = *(s + lenSx);
    char chT0 = *(t + lenTx);

    if ( chS0 == chT0 ) {
      throw runtime_error("should never have equal characters at the front");
    }

    size_t togoS = lenS - lenSx;
    size_t togoT = lenT - lenTx;
    
    if ( togoS >= 2 && togoT >= 2 ) {
      char chS1 = *(s + lenSx + 1);
      char chT1 = *(t + lenTx + 1);
      if ( chS0 == chT1 && chS1 == chT0 ) {
	// transpose
	Score next(current);
	next.advance(1, 2, 2);
	insert(next);
	current.invalidate();
	continue;
      }
    }

    // try all of insert, delete, and change for s2 -> s1

    // TODO:  try to optimize this...

    Score ins(current);
    ins.advance(1, 1, 0);
    insert(ins);

    Score del(current);
    del.advance(1, 0, 1);
    insert(del);

    Score ch(current);
    ch.advance(1, 1, 1);
    insert(ch);

    current.invalidate();
  }

  throw runtime_error("dropped out of loop in distance2");
}

void DistanceWithTranspose::clear()
{
  std::vector<Score *>::iterator i;
  for ( i = scores.begin() ; i != scores.end() ; ++i ) {
    delete *i;
  }
  scores.clear();
}

struct Compare 
{
  bool operator()(Score const * p1, Score const * p2)
  {
    return (*p1) < (*p2);
  }
};

bool DistanceWithTranspose::empty() const
{
  Compare comp;
  sort(scores.begin(), scores.end(), comp);
  return scores.empty() || ! scores.front()->isValid();
}

Score & DistanceWithTranspose::get()
{
  Score & score = *(scores.front());
  return score;
}

void DistanceWithTranspose::insert(Score & score)
{
  /* try some shortcuts that always apply */

  /*
   * first, strip off identical characters at the front, which
   * doesn't change the score.
   */
  for ( ;; ) {
    size_t lenSx = score.getOffset1();
    if ( lenS <= lenSx ) {
      break;
    }
    size_t lenTx = score.getOffset2();
    if ( lenT <= lenTx ) {
      break;
    }
    char chS = *(s + lenSx);
    char chT = *(t + lenTx);
    if ( chS != chT ) {
      break;
    }

    score.advance(0, 1, 1);
  }

  /*
   * Second, if either string is empty, we can shortcut to the end by
   * adding the length of the other string to the score and go to the
   * end state.
   */

  size_t lenSx = score.getOffset1();
  size_t lenTx = score.getOffset2();
  if ( lenS == lenSx ) {
    size_t x = lenT - lenTx;
    score.advance(x, 0, x);
  }
  else if ( lenT == lenTx ) {
    size_t x = lenS - lenSx;
    score.advance(x, x, 0);
  }

  size_t curr = score.getScore();
  if ( curr >= best ) {
    return;
  }


  /**
   * now, make sure that the (possibly modified) score is not already
   * pending with a score <= to the current.
   */
  lenSx = score.getOffset1();
  lenTx = score.getOffset2();

  std::vector<Score *>::iterator i;
  for ( i = scores.begin() ; i != scores.end() ; ++i ) {
    Score & test = *(*i);
    size_t lenSi = test.getOffset1();
    size_t lenTi = test.getOffset2();
    if ( lenSi == lenSx && lenTi == lenTx ) {
      if ( test.getScore() > curr ) {
	// the old one was worse, so substitute this version
	test = score;
      }
      break;
    }
  }

  if ( lenSx == lenS && lenTx == lenT && curr < best ) {
    best = curr;
  }

  if ( i == scores.end() ) {
    scores.push_back(new Score(score));
    ++inserts;
  }
}
