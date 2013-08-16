#if ! defined(ListMaker_h)
#define ListMaker_h 1

#include <vector>

class Generator;

class ListMaker
{
public:
  ListMaker();
  ListMaker(int argc, char ** argv);

  std::vector<int> make();

private:
  size_t lim;
  bool   sorted;
  size_t output;
  size_t prefix;
  size_t middle;
  bool   exponential;

  void initVars();
  void parseArgs(int argc, char ** argv);
  void randomize(std::vector<int> & p);
  Generator * makeGenerator() const;

};

#endif // not defined ListMaker_h
