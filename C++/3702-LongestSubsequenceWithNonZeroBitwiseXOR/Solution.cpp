#include <vector>

class Solution {
 public:
  int longestSubsequence(std::vector<int>& nums) {
    // Find longest subsequence with non-zero XOR.
    //
    // Take the entire array. If xorSum is 0, then either all are 0s, or
    // we can simply remove one element.
    const auto n = static_cast<int>(nums.size());

    auto xorSum = 0;
    bool allZero = true;

    for (auto x : nums) {
      xorSum ^= x;
      allZero = allZero && (x == 0);
    }

    if (xorSum > 0) {
      return n;
    }

    return allZero ? 0 : n - 1;
  }
};
