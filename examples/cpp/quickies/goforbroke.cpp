
#include <iostream>
#include <map>


typedef std::map<int, double> value_probability_map;
typedef value_probability_map::const_iterator vpm_iter;


const int contract_cost = 1;

const int initial_amount = contract_cost * 20;

const double payoff_probability = 0.1;

const int contract_payoff = contract_cost * 12;

const int periods = 30 * 12;

const double epsilon = 1e-12;


int main(int argc, char ** argv)
{
  value_probability_map vpm;
  vpm[initial_amount] = 1.0;

  value_probability_map next;

  for ( int t = 0 ; t < periods ; ++t ) {
    for ( vpm_iter i = vpm.begin() ; i != vpm.end() ; ++i ) {
      int    v = i->first;
      double p = i->second;

      if ( v == 0 ) {
	next[v] += p;
	continue;
      }
      
      int win_v = v + contract_payoff - contract_cost;
      double win_p = p * payoff_probability;
      if ( win_p  > epsilon ) {
	next[win_v] += win_p;
      }

      int lose_v = v - contract_cost;
      double lose_p = p * (1 - payoff_probability);
      if ( lose_p > epsilon ) {
	next[lose_v] += lose_p;
      }
    }

    vpm = next;
    next = value_probability_map();
  }

  double e = 0.0;
  double w = 0.0;
  for ( vpm_iter i = vpm.begin() ; i != vpm.end() ; ++i ) {
    std::cout << i->first << "  " << i->second << std::endl;
    e += i->first * i->second;
    w += i->second;
  }

  std::cout << std::endl;
  std::cout << "Expected value:  " << (e/w) << std::endl;
  std::cout << "Final weights: " << w << std::endl;
  
  

  return 0;
}
