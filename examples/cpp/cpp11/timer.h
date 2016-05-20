#if ! defined(TIMER_H)
#define TIMER_H  1

#include <chrono>
#include <string>
#include <sstream>

template <typename Action>
class Timer
{
  using time_pt = std::chrono::time_point<std::chrono::system_clock>;
  using dur = std::chrono::duration<double>;

public:
  Timer(Action & a) 
    : action(a)
  {
    start = std::chrono::system_clock::now();
  }

  ~Timer()
  {
    time_pt end = std::chrono::system_clock::now();
    dur elapsed_seconds = end-start;

    std::stringstream s;
    s << elapsed_seconds.count() << " seconds";
    std::string msg = s.str();
    action(msg);
  }
private:
  Action action;
  time_pt start;
};

template <typename Action>
auto make_timer(Action & a) -> Timer<Action>
{
  return Timer<Action>(a);
}


#endif // TIMER_H
