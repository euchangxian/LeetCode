#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<int> applyOperations(std::vector<int>& nums) {
    // non-negative integers.
    // Apply n-1 operations. On the ith operation,
    // - if nums[i] == nums[i+1], then nums[i] *= 2, nums[i+1] = 0;
    //   Otherwise, skip
    // Shift all 0s to the end of the array.
    // Two pointer simulation works.
    for (int i = 0; i < nums.size() - 1; ++i) {
      if (nums[i] == nums[i + 1]) {
        nums[i] <<= 1;
        nums[i + 1] = 0;
        ++i;  // skip the 0-ed out element.
      }
    }

    int writeIdx = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i]) {
        nums[writeIdx++] = nums[i];
      }
    }

    while (writeIdx < nums.size()) {
      nums[writeIdx++] = 0;
    }
    return nums;
  }
};
