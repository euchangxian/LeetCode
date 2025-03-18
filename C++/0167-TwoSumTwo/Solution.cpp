#include <vector>

class Solution {
 public:
  std::vector<int> twoSum(std::vector<int>& nums, int target) {
    int i = 0;
    int j = nums.size() - 1;

    while (i < j) {
      int sum = nums[i] + nums[j];
      if (sum == target) {
        break;
      }

      if (sum > target) {
        --j;
        continue;
      }
      ++i;
    }
    return {i + 1, j + 1};
  }
};
