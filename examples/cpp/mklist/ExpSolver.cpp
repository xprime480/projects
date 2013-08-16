
#include <cmath>

#include "ExpSolver.h"

using namespace std;

namespace {
  class ExpSolver
  {
  public:
    ExpSolver(double _p, double _r, double _d, int _N, int _H);

    void exec();

    double newP() const;
    double newR() const;
    double newDelta() const;

  private:
    double const p;
    double const r;
    double const delta;
    double const N;
    double const H;
    double oMin;
    int argminP;
    int argminR;

    void test(int pm, int rm);
  };

  double f(double p, double r, int N);
  double obj(double p, double r, int N, int H);

  ExpSolver::ExpSolver(double _p, double _r, double _d, int _N, int _H)
    : p(_p)
    , r(_r)
    , delta(_d)
    , N(_N)
    , H(_H)
    , oMin(obj(p, r, N, H))
    , argminP(0)
    , argminR(0)
  {
  }

  void ExpSolver::exec()
  {
    test(-1, -1);
    test(-1,  0);
    test(-1,  1);

    test( 0, -1);
    test( 0,  1);

    test( 1, -1);
    test( 1,  0);
    test( 1,  1);
  }

  double ExpSolver::newP() const
  {
    return p + argminP * delta;
  }

  double ExpSolver::newR() const
  {
    return r + argminR * delta;
  }

  double ExpSolver::newDelta() const 
  {
    if ( argminP == 0 && argminR == 0 ) {
      return delta / 10.0;
    }
    
    return delta;
  }

  void ExpSolver::test(int pm, int rm)
  {
    double o = obj(p + pm * delta, r + rm * delta, N, H);
    if ( o < oMin ) {
      oMin = o;
      argminP = pm;
      argminR = rm;
    }
  }

  double f(double p, double r, int N)
  {
    if ( p <= 0.0 ) {
      return 0;
    }
    if ( r >= 1.0 || r <= 0.0 ) {
      return 0;
    }
    return p * (1 - pow(r, N+1)) / (1 - r);
  }

  double obj(double p, double r, int N, int H)
  {
    double f1 = f(p, r, N) - 1.0;
    double f2 = f(p, r, H) - 0.5;

    return (f1*f1) + (f2*f2);
  }


}

pair<double, double> solve(int N, int H)
{
  double p = 0.15;
  double r = 0.95;

  double delta = 0.1;

  while ( delta >= 1e-8 ) {
    ExpSolver step(p, r, delta, N, H);
    step.exec();
    p = step.newP();
    r = step.newR();
    delta = step.newDelta();
  }

  return make_pair(p, r);
}
