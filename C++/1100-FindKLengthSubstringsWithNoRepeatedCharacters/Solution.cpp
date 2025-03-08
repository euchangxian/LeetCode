#include <array>
#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  int numKLenSubstrNoRepeats(std::string_view s, int k) {
    // Return number of substrings in S of length k with no repeated characters
    // Fixed size sliding window, maintain frequency array and unique characters
    // count.
    // The count must be equal to k for the window to be valid.
    std::array<int, 26> freq{};

    int result = 0;
    int unique = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (freq[s[i] - 'a']++ == 0) {
        ++unique;
      }

      if (i >= k) {
        if (--freq[s[i - k] - 'a'] == 0) {
          --unique;
        }
      }

      if (i >= k - 1 && unique == k) {
        ++result;
      }
    }
    return result;
  }
};
