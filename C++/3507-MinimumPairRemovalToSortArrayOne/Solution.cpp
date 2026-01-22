#include <algorithm>
#include <limits>
#include <vector>

class Solution {
 public:
  int minimumPairRemoval(std::vector<int>& nums) {
    // perform any number of times:
    // - select adjacent pair with minimum sum in nums, choose leftmost one if
    //   multiple exists.
    // - replace the pair with their sum.
    // Return the minimum number of operations to make the array non-decreasing.
    //
    // Hm. Are we guaranteed to have a solution?
    // Seems like we may need to replace sorted-pairs too, since we are only
    // allowed to perform operations on min-sum pairs.
    // Sigh. Just simulate I guess.
    auto minPairIndex = [](const auto& nums) {
      const auto n = static_cast<int>(nums.size());
      auto minSum = std::numeric_limits<int>::max();
      auto idx = -1;
      for (int i = 0; i < n - 1; ++i) {
        if (auto sum = nums[i] + nums[i + 1]; sum < minSum) {
          minSum = sum;
          idx = i;
        }
      }
      return idx;
    };

    auto mergePair = [](auto& nums, auto idx) {
      nums[idx] += nums[idx + 1];
      nums.erase(nums.begin() + idx + 1);
    };

    int result = 0;
    while (!std::ranges::is_sorted(nums)) {
      mergePair(nums, minPairIndex(nums));
      ++result;
    }
    return result;
  }
};
