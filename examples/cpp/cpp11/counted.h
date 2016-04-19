#if ! defined(COUNTED_H)
#define COUNTED_H 1

class Counted
{
public:
  Counted();
  ~Counted();

private:
  int serial_number;
  static int counter;
};

#endif /* COUNTED_H */
