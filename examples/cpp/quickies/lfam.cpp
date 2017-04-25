
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

template <typename Ret>
auto bobo(std::function<Ret()> gen) -> std::map<int, Ret>
{
    std::map<int, Ret> rv;
    for ( int i = 0 ; i < 13 ; ++i ) {
	rv[i] = gen();
    }
    return rv;
}

template <typename K, typename V>
std::ostream & operator<<(std::ostream & os, const std::pair<K,V> & kv)
{
    os << "{" << kv.first << "/" << kv.second << "}";
    return os;
}

template <typename Coll>
void dump(const Coll & c)
{
    for ( auto d : c ) {
	std::cout << d << " ";
    }
    std::cout << std::endl;
}

template <typename K, typename V, typename... Rest>
void dump(const std::map<K, V, Rest...> & m)
{
    for ( auto d : m ) {
	std::cout << d.second << " ";
    }
    std::cout << std::endl;
}

void test1()
{
    static int counter { 0 };
    std::function<int()> gen = [&](){ return ++counter; };
    auto v = bobo(gen);
    dump(v);
}

void test2()
{
    static double counter { 1.0 };
    std::function<double()> gen = [&](){ double x = counter; counter *= 1.5; return x; };
    auto v = bobo(gen);
    dump(v);
}

void test3()
{
    //    auto v = bobo([&](){ return 7; });
    //    dump(v);
}

struct Foo
{
    Foo()
	: counter{ 'A' }
    {
    }

    int operator()()
    {
	char rv = counter;
	++counter;
	return rv;
    }

private:
    char counter;
};

void test4()
{

    Foo f;
    std::function<char()> g = std::bind(&Foo::operator(), &f);
    auto v = bobo(g);
    dump(v);
}

int someInt()
{
    return 3;
}

void test5()
{

    std::function<int()> g = someInt;
    auto v = bobo(g);
    dump(v);
}

int main(int, char **)
{
    test1();
    test2();
    test3();
    test4();
    test5();

    return 0;
}
