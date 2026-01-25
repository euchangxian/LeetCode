#include <algorithm>
#include <vector>

class Solution {
 public:
  int minimumDifference(std::vector<int>& nums, int k) {
    // Pick any k nums such that the difference of the highest and lowest of
    // the k scores is minimised.
    //
    // Sort, k sliding window?
    const auto n = static_cast<int>(nums.size());
    std::ranges::sort(nums);

    int result = nums.back() - nums.front();
    for (int l = 0, r = k - 1; r < n; ++l, ++r) {
      result = std::min(result, nums[r] - nums[l]);
    }
    return result;
  }
};
