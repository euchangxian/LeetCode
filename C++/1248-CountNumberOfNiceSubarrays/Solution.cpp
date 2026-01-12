#include <vector>

class Solution {
 public:
  int numberOfSubarrays(std::vector<int>& nums, int k) {
    // A continuous subarray is nice if there are k odd numbers on it.
    // Return the number of nice subarrays.
    //
    // Sliding Window?
    // If < k, slide right. if = k, add to result, if > k, shrink.
    // Seems about right.
    // NOPE.
    //
    // Transform the problem into <= k odd numbers.
    // Then, to solve this problem:
    // if <= k, slide right, add r-l+1 to result, if > k, shrink
    const auto n = static_cast<int>(nums.size());

    auto atMostK = [&](auto k) {
      int result = 0;
      for (int l = 0, r = 0; r < n; ++r) {
        k -= nums[r] & 1;

        while (k < 0) {
          k += nums[l++] & 1;
        }
        result += r - l + 1;
      }
      return result;
    };

    return atMostK(k) - atMostK(k - 1);
  }
};
