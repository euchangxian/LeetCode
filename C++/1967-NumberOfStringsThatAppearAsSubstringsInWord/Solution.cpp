#include <iterator>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  int numOfStrings(std::vector<std::string>& patterns, std::string_view word) {
    // Return the number of strings in patterns that exists as a substring in
    // word.
    return std::ranges::distance(
        patterns | std::views::filter([word](std::string_view pattern) {
          return word.contains(pattern);
        }));
  }
};
