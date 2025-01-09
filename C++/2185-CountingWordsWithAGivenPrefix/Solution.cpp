#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  int prefixCount(std::vector<std::string>& words, std::string_view pref) {
    // number of words that have the given prefix.
    auto hasPrefix = [pref = pref](std::string_view word) -> bool {
      return word.starts_with(pref);
    };

    return std::ranges::count_if(words.begin(), words.end(), hasPrefix);
  }
};
