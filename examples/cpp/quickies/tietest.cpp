
#include <set>
#include <iostream>
#include <tuple>

int main(int, char **)
{
    using tt = std::set<int>;
    tt aSet;
    bool wasInserted;

    std::tie(std::ignore, wasInserted) = aSet.insert(3);
    std::cout << std::boolalpha << wasInserted << std::endl;
}
