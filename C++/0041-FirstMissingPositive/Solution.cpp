#include <cmath>
#include <vector>

class Solution {
 public:
  int firstMissingPositive(std::vector<int>& nums) {
    // Given unsorted nums, find the smallest positive integer in nums that is
    // not present, using O(N) time, O(1) space.
    // Note that nums[i] <= 0 is possible.
    //
    // Something like MEX.
    // Thus, the answer is in the range [1..n], where ignoring negative
    // integers, if the number of positives is equal to n, then 1..n must be
    // present, and the answer is n+1.
    const int n = nums.size();
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] <= 0 || nums[i] > n) {
        nums[i] = n + 1;
      }
    }

    for (int i = 0; i < n; ++i) {
      int x = std::abs(nums[i]);

      if (x > n) {
        continue;  // previously marked.
      }

      // mark the "sorted" position of x.
      if (nums[x - 1] > 0) {
        nums[x - 1] *= -1;
      }
    }

    for (int i = 0; i < n; ++i) {
      if (nums[i] > 0) {
        return i + 1;
      }
    }
    return n + 1;
  }
};
