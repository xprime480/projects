#if ! defined(Analyzer_h)
#define Analyzer_h 1

#include <string>
#include <vector>

#include "Formatter.h"

class Analyzer
{
public:
  Analyzer(Formatter const & formatter);

  void read(std::vector<std::string> const & files);
  void write() const;

protected:
private:
};

#endif
