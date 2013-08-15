#if ! defined(Collector_h)
#define Collector_h 1

#include <vector>

class Collector
{
 public:
  typedef int DataType;

  Collector();

  void add(DataType val);
  
  int count() const;
  DataType min() const;
  DataType max() const;
  DataType sum() const;
  double avg() const;
  double var() const;

  void report() const;

 protected:

 private:
  std::vector< DataType > data;
  DataType min_val;
  DataType max_val;
};


#endif
