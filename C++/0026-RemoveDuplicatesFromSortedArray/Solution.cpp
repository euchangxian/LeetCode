#include <vector>

class Solution {
 public:
  int removeDuplicates(std::vector<int>& nums) {
    int insertIdx = 1;  // nums[:i] is sorted
    for (size_t i = 1; i < nums.size(); ++i) {
      if (nums[i] == nums[i - 1]) {
        continue;  // Duplicate element.
      }
      nums[insertIdx] = nums[i];
      ++insertIdx;
    }

    return insertIdx;
  }
};
