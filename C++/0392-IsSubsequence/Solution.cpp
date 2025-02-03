#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  bool isSubsequence(std::string_view s, std::string_view t) {
    // return true if s is a subsequence of t
    auto it = s.begin();
    for (char c : t) {
      if (c == *it) {
        ++it;
      }
    }

    return it == s.end();
  }
};
