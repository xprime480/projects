#if ! defined(Score_h)
#define Score_h 1

class Score
{
public:

  Score(size_t _s, size_t _t, size_t v);
  Score(Score const & _s);

  Score & operator=(Score const & _s);

  size_t getOffset1() const;
  size_t getOffset2() const;

  size_t getScore() const;

  void advance(size_t sc, size_t ss, size_t st);

  bool isValid() const;
  void invalidate();

  bool operator<(Score const & s2) const;

private:
  bool valid;
  size_t s;
  size_t t;
  size_t score;
};

#endif // not defined Score_h
