#if ! defined(TIMER_H)
#define TIMER_H  1

#include <chrono>

class Timer
{
public:
  Timer()
  {
  }

  void start()
  {
    beg = std::chrono::system_clock::now();
  }

  void stop()
  {
    end = std::chrono::system_clock::now();
  }

  using dur = std::chrono::duration<double>;
  dur duration() const
  {
    return end-beg;
  }

private:
  using time_pt = std::chrono::time_point<std::chrono::system_clock>;
  time_pt beg;
  time_pt end;
};

#endif // TIMER_H
