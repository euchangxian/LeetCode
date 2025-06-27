#include <bit>
#include <string_view>

class Solution {
 public:
  int longestSubsequence(std::string_view s, int k) {
    // Given binary string s, integer k > 0.
    // Return the length of the longest subsequence that makes up a binary
    // number <= k.
    // - The subsequence can contain leading 0s.
    //
    // First glance seems like greedy, where we kinda want to pick '0's and
    // drop previously picked '1's.
    // Though, when iterating from the front, all bits get shifted left upon
    // adding a new bit.
    // May be simpler to iterate from reverse.
    int sum = 0;
    int result = 0;
    int maxBit = 32 - std::countl_zero(static_cast<unsigned int>(k));

    for (int i = 0; i < s.size(); ++i) {
      // reverse
      char bit = s[s.size() - 1 - i];

      if (bit == '0') {
        ++result;
        continue;
      }

      if (i < maxBit && sum + (1 << i) <= k) {
        sum += 1 << i;
        ++result;
      }
    }
    return result;
  }
};
