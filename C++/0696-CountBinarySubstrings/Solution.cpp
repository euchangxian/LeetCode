#include <algorithm>
#include <string_view>
#include <utility>

class Solution {
 public:
  int countBinarySubstrings(std::string_view s) {
    // Return the number of non-empty substrings that have the same number of
    // 0s and 1s, with the 0s and 1s grouped consecutively.
    //
    // Count the groups.
    int result = 0;
    int prev = 0;
    int curr = 1;
    for (int i = 1; i < s.size(); ++i) {
      if (s[i] == s[i - 1]) {
        ++curr;
      } else {
        result += std::min(prev, curr);
        prev = std::exchange(curr, 1);
      }
    }
    return result + std::min(prev, curr);
  }
};
