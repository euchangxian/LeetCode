#include <vector>

class Solution {
 public:
  std::vector<int> leftRightDifference(std::vector<int>& nums) {
    // leftSum[i] = prefix sum exclusive of index i
    // rightSum[i] = suffix sum exclusive of index i
    // Return answer[i] = |lsum[i] - rsum[i]|
    const auto n = static_cast<int>(nums.size());

    std::vector<int> psum(n);
    psum[0] = 0;
    auto total = 0;
    for (auto i = 1; i < n; ++i) {
      psum[i] = psum[i - 1] + nums[i - 1];
      total += nums[i - 1];
    }
    total += nums.back();

    for (auto i = 0; i < n; ++i) {
      nums[i] = std::abs(psum[i] - (total - psum[i] - nums[i]));
    }
    return nums;
  }
};
