#include <algorithm>
#include <cmath>
#include <vector>

class Solution {
 public:
  int getMinDistance(std::vector<int>& nums, int target, int start) {
    // Find i such that nums[i] == target, abs(i - start) is minimised.
    // target is guaranteed to exist.
    const auto n = static_cast<int>(nums.size());

    auto result = n;
    for (int i = 0; i < n; ++i) {
      if (nums[i] == target) {
        result = std::min(result, std::abs(start - i));
      }
    }
    return result;
  }
};
