#include <array>
#include <string_view>

class Solution {
 public:
  int countLetters(std::string_view s) {
    // sliding window.
    // condition for shrink is when uniq chars != 1
    int result = 0;
    std::array<int, 26> freq{};
    int unique = 0;
    int l = 0;
    for (int r = 0; r < s.size(); ++r) {
      if (freq[s[r] - 'a']++ == 0) {
        ++unique;
      }

      while (unique > 1) {
        if (--freq[s[l] - 'a'] == 0) {
          --unique;
        }
        ++l;
      }
      result += r - l + 1;
    }
    return result;
  }
};
