
class Counted
{
public:
  Counted();
  ~Counted();

private:
  int serial_number;
  static int counter;
};

