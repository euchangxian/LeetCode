#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  bool check(std::vector<int>& nums) {
    // Check if nums was originally sorted in non-decreasing order, then rotated
    // by some k >= 0 (rightwards).
    // At most one decreasing, i.e., peak. No need to count the rotation too.
    // O(n), O(logN) is not possible since we are not guaranteed that the
    // array was originally sorted.
    bool hasDecreasing = false;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] >= nums[i - 1]) {
        continue;
      }

      if (hasDecreasing) {
        return false;
      }
      hasDecreasing = true;
    }

    // If array has no decreasing patterns, then simply return true.
    // Otherwise, check that the front of the array is greater than the back.
    return !hasDecreasing || nums.front() >= nums.back();
  }
};
