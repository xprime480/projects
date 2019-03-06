#include <iostream>
#include <iterator>
#include <string>
#include <regex>

 
int main()
{
    std::string s = "This contains some numeric sub expressions like 123"
	" and 0.0005.  Done";
 
    std::regex number_regex("(\\d+\\.\\d+)|(\\d+)");

    auto numbers_begin = 
        std::sregex_iterator(s.begin(), s.end(), number_regex);
    auto numbers_end = std::sregex_iterator();
 
    std::cout << "Found "
              << std::distance(numbers_begin, numbers_end)
              << " numbers\n";
    for (std::sregex_iterator i = numbers_begin; i != numbers_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
	std::cout << "  " << match_str << '\n';
    }

    auto all_begin = 
        std::sregex_token_iterator(s.begin(), s.end(), number_regex, -1);
    auto all_end = std::sregex_token_iterator();
 
    std::cout << "Found "
              << std::distance(all_begin, all_end)
              << " tokens\n";
    for (std::sregex_token_iterator i = all_begin; i != all_end; ++i) {
        std::ssub_match match = *i;
        std::string match_str = match.str();
	std::cout << "  " << match_str << '\n';
    }
}
