
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    unordered_multimap<int, string> data {
	{ 0, "zero" },
	{ 1, "one" },
	{ 1, "eins" },
	{ 33, "thirty-three" }
    };

    for ( const auto & i : data ) {
	cout << i.first << " " << i.second << "\n";
    }

    cout << "\nWith equal_range\n";
    auto range = data.equal_range(1);
    for_each(range.first, range.second,
	     [](unordered_multimap<int, string>::value_type const & i) {
		 cout << i.first << " " << i.second << "\n";
	     });
}
