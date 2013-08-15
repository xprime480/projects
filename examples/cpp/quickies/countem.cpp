
#include <iostream>
#include <cstring>
#include <cstdlib>

/*
 * Count the number of ways to sum a subset of a given set of integers.
 */
class SummationCounter
{
public:
  /*
   * Create the counter.
   *
   * @param _size the number of integers to choose from the set
   * @param _min  the smallest number in the set
   * @param _max  the largest number in the set
   */
  SummationCounter(size_t _size, int _min, int _max)
    : size(_size)
    , min(_min)
    , max(_max)
  {
  }

  /*
   * Count the number of ways subsets of the counter can sum to a
   * given number.
   *
   * @param target the number to which the subsets should total.
   *
   * @return the number of distinct subsets
   */
  long run(int target)
  {
    long winners = 0;
    count(winners, min-1, 0, 0, target);
    return winners;
  }

private:
  /*
   * the number of integers to choose from the set
   */
  int size;
  /*
   * the low end of the set
   */
  int min;
  /*
   * the high end of the set
   */
  int max;

  /*
   * Given a partial solution, count the number of full solutions
   * which include it.
   *
   * @param winners reference to the number of solutions counted so
   *                far
   * @param last the position of the most recently used int in this 
   *             trail 
   * @param pos the number of integers already used
   * @param sum the partial sum from the first pos integers
   * @param target the desired total
   */
  void count(long & winners, int last, int pos, int sum, int target)
  {
    if ( sum >= target || pos == size ) {
      /*
       * We know that we can't add any more.  If we happen to be the
       * right size and the right total, we win, otherwise, give up.
       */
      if ( sum == target && pos == size ) {
	++winners;
      }
      return;
    }

    int start = last + 1;
    int t = sum + start * (size-pos);
    if ( t > target ) {
      return;			// guaranteed too big
    }
    int end = (target-sum) / (size-pos);
    if ( end > max ) {
      return; 			// guaranteed too small
    }
    for ( int i = start ; i <= end ; ++i ) {
      /*
       * If we get here, we might still have solution(s) available, so 
       * create another partial solution and recurse.
       */
      count(winners, i, pos+1, sum+i, target);
    }
  }
};

/*
 * Parameters for a SummationCounter
 */
struct Config {
  Config(int argc, char ** argv) 
    : startat( 1 )
    , stopat( 300 )
    , parts ( 5 )
    , smallest( 1 )
    , largest( 55 )
  {
    init(argc, argv);
  }

  void init(int argc, char ** argv)
  {
    setNextParm(argc, argv, startat);
    setNextParm(argc, argv, stopat);
    setNextParm(argc, argv, parts);
    setNextParm(argc, argv, smallest);
    setNextParm(argc, argv, largest);
  }
  
  static void help(char * name)
  {
    std::cout << "Usage: " << name << " start stop parts low high\n";
    std::cout << "Where:\n";
    std::cout << "\tstart is the smallest integer to partition\n";
    std::cout << "\tstop is the largest integer to partition\n";
    std::cout << "\tcount is the number of partitions\n";
    std::cout << "\tlow is the smallest integer for partitions\n";
    std::cout << "\thigh is the smallest integer for partitions\n";
  }

  int startat;
  int stopat;
  int parts;
  int smallest;
  int largest;

private:
  void setNextParm(int & argc, char **& argv, int & parm) {
    if ( ! argv ) {
      return;
    }
    --argc;
    ++argv;
    if ( argc <= 0 || ! *argv || 0 == std::strcmp("-", *argv) ) {
      return;
    }
    int i = std::atoi(*argv);
    if ( i <= 0 ) {
      std::cerr << "Warning: parameter should be positive integer: "
		<< *argv << "\n";
    }

    parm = i;
  }
};

int main(int argc, char** argv)
{
  if ( argc >= 2 && 0 == strcmp("--help", argv[1]) ) {
    Config::help(argv[0]);
    return 0;
  }

  Config config(argc, argv);
  SummationCounter c(config.parts, config.smallest, config.largest);
  for ( int i = config.startat ; i <= config.stopat ; ++i ) {
    std::cout << i << ": " << c.run(i) << "\n";
  }
}
