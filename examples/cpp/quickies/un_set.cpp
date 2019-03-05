
#include <unordered_set>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **)
{
    unordered_set<string> us { "cat", "hat", "bat", "fat" };

    for ( const auto & i : us ) {
	cout << i << '\n';
    }

    cout << "----------------------------\n";

    unordered_multiset<string> ums { "cat", "hat", "bat", "fat", "cat" };

    for ( const auto & i : ums ) {
	cout << i << '\n';
    }
}
