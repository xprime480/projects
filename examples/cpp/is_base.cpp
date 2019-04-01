
#include <type_traits>
#include <iostream>

class SpecialMarkerClass {};

struct BaseOfX
{
    virtual ~BaseOfX() {}
    virtual void exec() const = 0;
};

template <typename T, bool Alloced>
struct Helper : public BaseOfX
{
    void exec() const
    {
	std::cout << "Base Case\n";
    }
};

template <typename T>
struct Helper<T, true> : public BaseOfX
{
    void exec() const
    {
	std::cout << "Alloced Case\n";
    }
};

template <typename T>
struct X : public Helper<T, std::is_base_of<SpecialMarkerClass, T>::value>
{
};

class Random {};
class Arbitrary : public SpecialMarkerClass {};

int main(int, char**)
{
    X<Random> xr;
    X<Arbitrary> xa;

    xr.exec();
    xa.exec();

}
