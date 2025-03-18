#include <cstddef>
#include <vector>

class Solution {
 public:
  void moveZeroes(std::vector<int>& nums) {
    // Seems like two pointer where the first k elements are non-zeros
    // Similar to Remove Duplicates from Sorted array, where the relative order
    // of the elements must be maintained.
    size_t insertIdx = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
      if (nums[i] == 0) {
        continue;
      }
      const int num = nums[i];
      nums[i] = 0;  // zero out the original. This enables a single traversal
      nums[insertIdx] = num;
      ++insertIdx;
    }
  }
};
