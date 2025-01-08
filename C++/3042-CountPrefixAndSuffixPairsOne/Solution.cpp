#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  int countPrefixSuffixPairs(std::vector<std::string>& words) {
    // define isPrefixAndSuffix(s1, s2) that returns true iff s1 is both a
    // prefix and suffix of s2.
    // Want: i < j such that isPrefixAndSuffix(i, j) is true
    // O(n^2) naively.
    auto isPrefixAndSuffix = [](std::string_view s1,
                                std::string_view s2) -> bool {
      return s2.starts_with(s1) && s2.ends_with(s1);
    };

    int count = 0;
    for (int i = 0; i < words.size(); ++i) {
      for (int j = i + 1; j < words.size(); ++j) {
        count += isPrefixAndSuffix(words[i], words[j]);
      }
    }
    return count;
  }
};
