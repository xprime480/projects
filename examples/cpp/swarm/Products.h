#if ! defined(Products_h)
#define Products_h 1

/* test */

#include <map>

class Product
{
public:
  Product();
  void report() const;

  double objective(int Rate) const;

  int getMinRate() const;
  int getMaxRate() const;
  int getOptRate() const;

  int getKey() const;

private:
  int Key;

  // double Q0;
  // double beta;

  int rateMin;
  int rateMax;
  int rateOptPrior;

  int rateOpt;
  
  enum { NumRates = 101 };
  mutable std::map<int, double> objectives;

  static int KeySource;

  double computeObjective(int Rate) const;

};

#endif
