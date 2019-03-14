
#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <regex>
#include <set>
#include <vector>

using namespace std;

/**
 * findLastOf
 *
 * input - vector of characters to search in
 * c     - character to search for
 *
 * return - The index where the character is found
 *          -1 if not found.
 */
size_t findLastOf(vector<char> const & input, char c)
{
    for ( size_t i = input.size() - 1 ; i >= 0 ; --i ) {
        if ( c == input[i] ) {
            return i;
        }
    }

    return -1;
}

class Segmenter
{
public:
    Segmenter(vector<char> const & input)
        : input(input)
        , left(0)
        , right(0)
    {
    }

    vector<int> getSegmentLengths()
    {
        if ( input.empty() || answer.size() > 0 ) {
            return answer;
        }

        while ( left < input.size() ) {
            /*
             * We are at the start of a new segment.  Note the
             * starting character and find the last occurence of
             * it.
             */
            char first = input[left];
            seenChars.insert(first);
            right = findLastOf(input, first);

            /*
             * Keep extending the right endpoint until we run out of
             * new characters to check.
             */
            extendRight();

            /*
             * input[left..right] is now the segment, compute its length.
             */
            answer.push_back(right - left + 1);

            /*
             * Prepare for next pass.
             */
            left = right + 1;
            seenChars.clear();
        }

        return answer;
    }

private:
    vector<char> const & input;
    vector<int> answer;

    set<char> seenChars;
    size_t left;
    size_t right;

    /**
     * extractCharsToCheck
     *
     * return - a set that includes all characters between the
     *          current endpoints, excluding those characters
     *          which we have already processed.
     */
    set<char> extractCharsToCheck()
    {
        auto i = input.begin();
        advance(i, left);

        auto j = input.begin();
        advance(j, right);

        set<char> charsInRange(i, j);
        set<char> charsToCheck;
        set_difference(charsInRange.begin(), charsInRange.end(),
                       seenChars.begin(), seenChars.end(),
                       inserter(charsToCheck, charsToCheck.begin()));

        return charsToCheck;
    }

    /**
     * extendRight
     *
     * Extend the right endpoint by:
     *   - First get a set of characters which are in the current
     *     range but not yet processed.
     *   - Extend the right endpoint to the rightmost of the current
     *     right endpoint and the right endpoints of the ranges of
     *     the characters processed by this call.
     *
     * Side Effects:  update the list of seen characters, and the 
     *                right endpoint.
     */
    void extendRight()
    {
        set<char> charsToCheck;

        do {
            charsToCheck = extractCharsToCheck();
            for ( auto c : charsToCheck ) {
                size_t temp = findLastOf(input, c);
                right = max(right, temp);
                seenChars.insert(c);
            }
        } while ( ! charsToCheck.empty() );
    }
};


vector<int> parseOutput(char const * output)
{
    vector<int> answer;

    regex number_regex("(\\d+)", regex_constants::ECMAScript);
    auto numbers_begin =
        cregex_iterator(output, output + strlen(output), number_regex);
    auto numbers_end = cregex_iterator();

    for (cregex_iterator i = numbers_begin; i != numbers_end; ++i) {
        int n = atoi(i->str().c_str());
        answer.push_back(n);
    }

    return answer;
}

void compareResults(vector<int> const & expected,
                    vector<int> const & actual,
                    char const * name)
{
    cout << name << ":  ";
    if ( expected == actual ) {
        cout << "PASS\n";
    }
    else {
        cout << "FAIL\n";

        cout << "Expected: ";
        copy(expected.begin(), expected.end(),
             ostream_iterator<int>(cout, " "));
        cout << "\n";

        cout << "Actual: ";
        copy(actual.begin(), actual.end(),
             ostream_iterator<int>(cout, " "));
        cout << "\n";
    }
}

void test(char const * input, char const * output, char const * name)
{
    vector<char> chars(input, input + strlen(input));
    vector<int> expected = parseOutput(output);
    Segmenter s(chars);
    vector<int> actual = s.getSegmentLengths();
    compareResults(expected, actual, name);
}

int main()
{
    test("", "", "Null Input");
    test("a", "1", "Singleton");
    test("aa", "2", "Doubleton");
    test("ab", "1 1", "Two Singletons");
    test("aabb", "2 2", "Two Doubletons");
    test("abbba", "5", "Bookends");
    test("abacbc", "6", "Interleave");
    test("abacbcxdedfef", "6 1 6", "Two Interleave");
}
