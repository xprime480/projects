
#include <array>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

constexpr size_t ten() { return 10; }

int main(int argc, char ** argv)
{
    constexpr size_t N = ten();
    array<int, N> data { 1, -1, 0, 2, -2, -1234556 };

    cout << data.size() << "\n";
    cout << data.max_size() << "\n";
    copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";
}
