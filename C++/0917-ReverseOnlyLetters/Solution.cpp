#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>
#include <utility>

class Solution {
 public:
  std::string reverseOnlyLetters(std::string s) {
    const auto n = static_cast<int>(s.size());
    int l = 0;
    int r = n - 1;
    while (l < r) {
      if (!std::isalpha(s[l])) {
        ++l;
      } else if (!std::isalpha(s[r])) {
        --r;
      } else {
        std::swap(s[l++], s[r--]);
      }
    }
    return s;
  }
};
