
#include <functional>
#include <iostream>

struct X
{
    int p1,p2;
};


namespace std
{
    template<> struct hash<X>
    {
	typedef X argument_type;
	typedef std::size_t result_type;

	result_type operator()(argument_type const & x)
	{
	    result_type const h1 ( std::hash<int>{}(x.p1) );
	    result_type const h2 ( std::hash<int>{}(x.p2) );
	    return h1 ^ (h2 << 1);
	}
    };
}

int main(int argc, char ** argv)
{
    X const x { 99, 103 };
    std::cout << std::hash<X>{}(x) << "\n";
}
