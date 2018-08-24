

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

double mean(std::vector<double> const & vec)
{
    double sum = std::accumulate(vec.begin(), vec.end(), 0);
    return sum / (double) vec.size();
}

double variance(std::vector<double> const & vec)
{
    double mu = mean(vec);
    double sum = std::accumulate(vec.begin(), vec.end(), 0,
				 [&](double a, double b) -> double {
				     double t = b - mu;
				     return a + t*t;
				 });
    return sum / (double) vec.size();
}

void stats(std::vector<double> const & vec)
{
    std::cout << "Length:\t" << vec.size() << "\n";
    std::cout << "  Mean:\t" << mean(vec) << "\n";
    double v = variance(vec);
    std::cout << "   Var:\t" << v << "\n";
    std::cout << "Stddev:\t" << sqrt(v) << "\n";

    std::cout << "--------------------------------------\n\n";
}

void fill_vec(double len, std::vector<double> & vec)
{
    for ( double i = 1u ; i <= len ; ++i ) {
	vec.push_back(i);
    }

    stats(vec);
}

template <typename F>
void merge(std::vector<double> const & a, std::vector<double> const & b, F f)
{
    std::vector<double> c;

    for ( auto aa : a ) {
	for ( auto bb : b ) {
	    c.push_back(f(aa,bb));
	}
    }

    stats(c);
}

void test(double a, double b)
{
    std::vector<double> va;
    std::vector<double> vb;

    fill_vec(a, va);
    fill_vec(b, vb);

    merge(va, vb, [](double a, double b) -> double { return a+b; });
    merge(va, vb, [](double a, double b) -> double { return a*b; });
}

int main(int argc, char ** argv)
{
    test(5, 8);

    return 0;
}
