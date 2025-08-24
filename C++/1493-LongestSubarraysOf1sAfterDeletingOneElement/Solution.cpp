#include <algorithm>
#include <vector>

class Solution {
 public:
  int longestSubarray(std::vector<int>& nums) {
    // Given a binary array nums, delete exactly one element from it.
    // Return the size of the longest non-empty subarray containing only 1s.
    //
    // Sliding window with a tolerance of one. Expand while 1s, and at most 1
    // zero.
    // Shrink otherwise.
    const auto n = static_cast<int>(nums.size());

    int result = 0;
    int ones = 0;
    int zeroes = 0;
    for (int l = 0, r = 0; r < n; ++r) {
      ones += nums[r];
      zeroes += 1 - nums[r];
      while (zeroes > 1) {
        ones -= nums[l];
        zeroes -= 1 - nums[l];
        ++l;
      }
      result = std::max(result, r - l);
    }
    return result;
  }
};
