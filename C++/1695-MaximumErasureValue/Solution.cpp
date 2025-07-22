#include <algorithm>
#include <bitset>
#include <cstddef>
#include <vector>

constexpr std::size_t MAX_N = 1E4;

class Solution {
 public:
  int maximumUniqueSubarray(std::vector<int>& nums) {
    // Given positive integers, erase a subarray of unique elements.
    // The score is the sum of the subarray.
    // Return the maximum score by erasing exactly one.
    //
    // Since positive, we want to find the subarray that fulfils:
    // - all unique,
    // - largest sum
    // At first glance, sliding window.
    // This is because an element, once deemed invalid, will be invalid for
    // all subsequent elements.
    auto n = static_cast<int>(nums.size());

    std::bitset<MAX_N + 1> unique;
    int result = 0;
    int sum = 0;
    for (int l = 0, r = 0; r < n; ++r) {
      while (unique.test(nums[r])) {
        sum -= nums[l];
        unique.reset(nums[l]);
        ++l;
      }

      sum += nums[r];
      unique.set(nums[r]);
      result = std::max(result, sum);
    }

    return result;
  }
};
