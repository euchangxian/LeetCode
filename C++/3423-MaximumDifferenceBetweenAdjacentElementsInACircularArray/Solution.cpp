#include <algorithm>
#include <cmath>
#include <vector>

class Solution {
 public:
  int maxAdjacentDistance(std::vector<int>& nums) {
    // Given circular array nums, find the maximum absolute difference between
    // adjacent elements.
    int diff = std::abs(nums.back() - nums.front());
    for (int i = 1; i < nums.size(); ++i) {
      diff = std::max(diff, std::abs(nums[i] - nums[i - 1]));
    }
    return diff;
  }
};
