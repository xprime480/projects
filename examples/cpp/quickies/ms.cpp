
#include <iostream>
#include <memory>

class W
{
public:
    W(int a, int b, double c, bool d, char **** huh)
	: v(d ? a : b)
    {
    }

    W()
	: v(42)
    {
    }

    void remark() const
    {
	std::cout << "W here, right-o."  << std::endl;
	std::cout << "\t\t" << v << std::endl;
    }

private:
    int v;
};


int main(int, char **)
{
    std::shared_ptr<W> p = std::make_shared<W>(2, 3, 4.53, false, nullptr);
    p->remark();

    p = std::make_shared<W>();
    p-> remark();
}
