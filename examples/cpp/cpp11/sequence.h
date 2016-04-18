
template<typename T>
struct Sequence
{
  Sequence(T l, T h, T s)
    : lo(l)
    , hi(h)
    , step(s)
  {
  }

  T operator()()
  {
    if ( lo >= hi ) 
      throw "Out of bounds";
    T rv = lo;
    lo += step;
    return rv;
  }

private:
  T lo,hi,step;
};
