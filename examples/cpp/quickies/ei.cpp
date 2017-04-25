
#include <iostream>
#include <type_traits>
#include <string>

#if ! defined(REF_SIZE)
#define REF_SIZE 1
#endif

template <typename T> using tt = typename std::enable_if<sizeof(T) >= REF_SIZE, T>::type;

template <typename T, typename X = void>
struct F
{
    static void f()
    {
	std::cout << "Basic F\n";
    }
};

template <typename T>
struct F<T, typename std::enable_if<std::is_same<T, char>::value>::type>
{
    static void f()
    {
	std::cout << "Sneaky Char Version of F\n";
    }
};

template <typename T>
struct F<T, typename std::enable_if<std::is_integral<T>::value && ! std::is_same<T, char>::value>::type>
{
    static void f()
    {
	std::cout << "Integral F\n";
    }
};

template <typename T>
struct F<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
    static void f()
    {
	std::cout << "Floating F\n";
    }
};

int main(int argc, char ** argv)
{
    tt<int> x { 98 };
    std::cout << x << "\n";

    tt<char> y { 98 };
    std::cout << y << "\n";

    F<char>::f();
    F<unsigned char>::f();
    F<int>::f();
    F<double>::f();
    F<std::string>::f();
}
