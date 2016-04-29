#if ! defined(RB_H)
#define RB_H 1

#include <string>
#include <sstream>

template <typename T, typename... Ts>
class RB : public RB<Ts...>
{
private:
  using my_base = RB<Ts...>;

public:
  static std::string show()
  {
    std::stringstream s;
    s << "(" << sizeof(T) << " " << my_base::show() << ")";
    return s.str();
  }
};

template <typename T>
class RB<T>
{
public:
  static std::string show()
  {
    std::stringstream s;
    s << "(" << sizeof(T) << ")";
    return s.str();
  }
};

template <typename... Ts>
class RB<void, Ts...> : public RB<Ts...>
{
private:
  using my_base = RB<Ts...>;

public:
  static std::string show()
  {
    std::stringstream s;
    s << "(" << my_base::show() << ")";
    return s.str();
  }
};

template <>
class RB<void>
{
public:
  static std::string show()
  {
    return "()";
  }
};

#endif // RB_H
