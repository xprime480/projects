#if ! defined(SUMSIZES_H)
#define SUMSIZES_H 1

template <typename T, typename... Ts>
struct sumsizes
{
  static constexpr size_t sum = sizeof(T) + sumsizes<Ts...>::sum;
};

template <typename T>
struct sumsizes<T>
{
  static constexpr size_t sum = sizeof(T);
};

template <typename... Ts>
struct sumsizes<void, Ts...>
{
  static constexpr size_t sum = sumsizes<Ts...>::sum;
};

template <>
struct sumsizes<void>
{
  static constexpr size_t sum = 0;
};

#endif // SUMSIZES_H
