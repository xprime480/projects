
#include <iostream>
#include <iomanip>

struct SaveFormat
{
    SaveFormat(std::ostream & os)
	: f( os.flags() )
	, os( os )
    {
    }

    ~SaveFormat()
    {
	os.flags(f);
    }
    
private:
    std::ios::fmtflags f;
    std::ostream & os;
};

int main(int argc, char ** argv)
{
    {
	SaveFormat f(std::cout);
	double v { 3000000.00 };
	std::cout << v << "\n";
	std::cout << std::fixed << v << "\n";
	std::cout << std::setprecision(1) << v << "\n";
    }

    {
	SaveFormat f(std::cout);
	double v { .000003 };
	std::cout << v << "\n";
	std::cout << std::fixed << v << "\n";
	std::cout << std::setprecision(6) << v << "\n";
    }

    bool q = true;
    std::cout << q << "\n";
    {
	SaveFormat f(std::cout);
	std::cout << std::boolalpha << q << "\n";
    }
    std::cout << q << "\n";
}
