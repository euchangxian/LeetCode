#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maxAscendingSum(std::vector<int>& nums) {
    int best = nums[0];
    int curr = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] > nums[i - 1]) {
        curr += nums[i];
      } else {
        best = std::max(best, curr);
        curr = nums[i];
      }
    }

    return std::max(best, curr);
  }
};
