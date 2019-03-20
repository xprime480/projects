
#include <memory>
#include <iostream>

class C
{
public:
    C()
	: v(nextval++)
    {
    }

    C(C && other)
	: C()
    {
	v = other.v;
    }

    int get() const
    {
	return v;
    }

    template <typename T>
    friend T & operator<<(T & os, C const & c)
    {
	os << c.v;
	return os;
    }

private:
    int v;
    static int nextval;
};

int C::nextval { 1 };

int main()
{
    std::unique_ptr<C> a(new C);
    std::cout << a->get() << "\n";

    std::unique_ptr<C> b;
    b = std::move(a);
    std::cout << b->get() << "\n";
    std::cout << *b << "\n";

    double q { 5.75 };
    double r { 9.99 };

    std::swap(q, r);
    std::cout << q << "\n";
}
