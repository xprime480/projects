
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>

/** annual, from Schiller, 1871-2009 **/

double const historical_returns[] = {
  1.094594595 ,
  1.051440329 ,
  0.911937378 ,
  0.974248927 ,
  0.982378855 ,
  0.795964126 ,
  0.915492958 ,
  1.101538462 ,
  1.427374302 ,
  1.211350294 ,
  0.95638126  ,
  0.981418919 ,
  0.891566265 ,
  0.818532819 ,
  1.226415094 ,
  1.073076923 ,
  0.951612903 ,
  0.986817326 ,
  1.026717557 ,
  0.899628253 ,
  1.138429752 ,
  1.01814882  ,
  0.770053476 ,
  0.983796296 ,
  1.004705882 ,
  0.988290398 ,
  1.156398104 ,
  1.245901639 ,
  1.003289474 ,
  1.159016393 ,
  1.148514851 ,
  1.041871921 ,
  0.789598109 ,
  1.261976048 ,
  1.170818505 ,
  0.968591692 ,
  0.716527197 ,
  1.322627737 ,
  1.112582781 ,
  0.919642857 ,
  0.98381877  ,
  1.019736842 ,
  0.9	      ,
  0.893667861 ,
  1.247326203 ,
  1.025723473 ,
  0.753396029 ,
  1.088765603 ,
  1.124840764 ,
  0.805209513 ,
  1.026722925 ,
  1.219178082 ,
  0.992134831 ,
  1.198187995 ,
  1.195652174 ,
  1.059288538 ,
  1.308208955 ,
  1.418140331 ,
  0.873290426 ,
  0.736066329 ,
  0.519399249 ,
  0.854216867 ,
  1.486600846 ,
  0.878557875 ,
  1.485961123 ,
  1.278343023 ,
  0.642978965 ,
  1.105216622 ,
  0.984	      ,
  0.857723577 ,
  0.846445498 ,
  1.129899216 ,
  1.174430129 ,
  1.138396624 ,
  1.335804299 ,
  0.844062153 ,
  0.975016437 ,
  1.035738368 ,
  1.098958333 ,
  1.256516588 ,
  1.140499764 ,
  1.082265399 ,
  0.97249809  ,
  1.398271799 ,
  1.240168539 ,
  1.028992072 ,
  0.90512877  ,
  1.352626459 ,
  1.043329738 ,
  1.029122867 ,
  1.156563965 ,
  0.941942956 ,
  1.175069167 ,
  1.126487901 ,
  1.083604273 ,
  0.904950707 ,
  1.125399645 ,
  1.073653199 ,
  0.88504508  ,
  1.035212047 ,
  1.104931009 ,
  1.146369797 ,
  0.81160277  ,
  0.754968266 ,
  1.334895259 ,
  1.071753046 ,
  0.869376746 ,
  1.104819945 ,
  1.111924581 ,
  1.199332552 ,
  0.882003459 ,
  1.230133015 ,
  1.153323629 ,
  1.031372078 ,
  1.213157741 ,
  1.270522119 ,
  0.946958527 ,
  1.139452252 ,
  1.191163589 ,
  0.957437421 ,
  1.27827957  ,
  1.046024803 ,
  1.086758725 ,
  0.983636018 ,
  1.320623321 ,
  1.24706227  ,
  1.257289029 ,
  1.296265155 ,
  1.14159533  ,
  0.933599422 ,
  0.856701705 ,
  0.785679831 ,
  1.206286837 ,
  1.109722017 ,
  1.052417842 ,
  1.12229908  ,
  1.044337132 ,
  0.593258609 ,
  1.265303797
};

int const years = sizeof ( historical_returns ) / sizeof ( historical_returns[0] );


double trial()
{
  int const YEARS = 30;
  int const HOLD  = 2;
  double invested[HOLD + YEARS];
  double balance[HOLD];

  for ( int i = 0 ; i < HOLD ; ++i ) {
    invested[i] = 0.0;
    balance[i] = 0.0;
  }

  double losses_forward = 0;

  for ( int y = HOLD ; y < HOLD + YEARS ; ++y ) {

    double yield = 0.01 + ((double) rand()) / ((double) RAND_MAX) / 25.0;
    int index = (int) (years * ((double) rand()) / ((double) RAND_MAX));
    //int index = years - 1 - (30 * ((double) rand()) / ((double)
    //RAND_MAX));

    //int index = years - y;
    double performance = historical_returns[index];

    double div = 0.0;
    for ( int b = 0 ; b < HOLD ; ++b ) {
      div += yield * balance[b];
      balance[b] *= performance;
    }

    double value1 = balance[0];
    double value0 = invested[y-HOLD];

    double trading_profit = 0.0;

    if ( value1 < value0 ) {
      losses_forward += (value0 - value1);
      trading_profit = 0;
    }
    else {
      trading_profit = value1 - value0;
    }

    double total_profit = div + trading_profit;
    if ( total_profit > losses_forward ) {
      total_profit -= losses_forward;
      losses_forward = 0;
    }
    else {
      total_profit = 0;
      losses_forward -= total_profit;
    }

    double cash = value1 + div + 10000 - 2 * 10;
    double tax = 0.28 * total_profit;
    cash -= tax;

    for ( int b = 0 ; b < HOLD-1 ; ++b ) {
      balance[b] = balance[b+1];
    }

    balance[HOLD-1] = cash;
    invested[y] = cash;
  }

  double rv = 0.0;
  for ( int b = 0 ; b < HOLD ; ++b ) {
    rv += balance[b];
  }
  return rv;
}

void simulator()
{
  int const PASSES = 10000;
  double results[PASSES];

  for ( int i = 0 ; i < PASSES ; ++i ) {
    results[i] = trial();
  }

  std::sort(results, results+PASSES);

  std::cout << "minimum balance = " << results[0]           << std::endl;
  std::cout << "10 %ile balance = " << results[PASSES/10]   << std::endl;
  std::cout << "median  balance = " << results[PASSES/2]    << std::endl;
  std::cout << "90 %ile balance = " << results[9*PASSES/10] << std::endl;
  std::cout << "maximum balance = " << results[PASSES-1]    << std::endl;

}


int main(int argc, char ** argv)
{
  srand(time(0));
  simulator();
}
