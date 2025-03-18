#include <algorithm>
#include <vector>

class Solution {
 public:
  // Difference from House Robber One is that the houses are arranged in a
  // circle. That means that the first and last house are adjacent
  int rob(std::vector<int>& nums) {
    if (nums.size() == 1) {
      return nums[0];
    }
    // Since the first and the last house cannot be robbed at the same time,
    // take the max of robRow(nums[0:n-1]) and robRow(nums[1:n])
    int n = nums.size();
    return std::max(robRow(nums, 0, n - 1), robRow(nums, 1, n));
  }

 private:
  // adapted from House Robber One
  int robRow(std::vector<int>& nums, int begin, int end) {
    int currMax = 0;
    int prevMax = 0;

    for (int i = begin; i < end; ++i) {
      int newMax = std::max(currMax, prevMax + nums[i]);

      prevMax = currMax;
      currMax = newMax;
    }
    return currMax;
  }
};
