#include <algorithm>
#include <limits>
#include <vector>

using i64 = long long;

class Solution {
 public:
  i64 maxSubarraySum(std::vector<int>& nums, int k) {
    // Return the max sum of a subarray of nums such that the size of the
    // subarray is divisible by k.
    // 1 <= k <= nums.length <= 2E5
    // -ve <= nums[i] <= +ve
    //
    // Hm. Naively, iterate over subarrays of size m*k. But this is too slow
    // considering k is not bounded, and k <= nums.length.
    //
    // We do not want to have to keep track of length. Just need it to be
    // divisible by k.
    // Prefix Sum?
    // (b - a) % k == 0
    // => ((b%k)-(a%k))%k == 0
    const auto n = static_cast<int>(nums.size());

    // minimum prefix sum ending at index i, modulo k.
    std::vector<i64> minPrefix(k, std::numeric_limits<i64>::max() / 2);
    minPrefix[k - 1] = 0;

    i64 prefix = 0;
    i64 result = std::numeric_limits<i64>::min() / 2;
    for (int i = 0; i < n; ++i) {
      prefix += nums[i];

      int remainder = i % k;
      result = std::max(result, prefix - minPrefix[remainder]);

      minPrefix[remainder] = std::min(minPrefix[remainder], prefix);
    }
    return result;
  }
};
