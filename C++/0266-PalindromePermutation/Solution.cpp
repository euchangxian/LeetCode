#include <string_view>

class Solution {
 public:
  bool canPermutePalindrome(std::string_view s) {
    // parity.
    int mask = 0;
    for (char c : s) {
      mask ^= 1 << (c - 'a');
    }

    return __builtin_popcount(mask) <= 1;
  }
};
