#include <algorithm>
#include <vector>

class Solution {
 public:
  int minSwaps(std::vector<int>& nums) {
    int n = nums.size();

    int windowSize = 0;  // number of ones
    for (int num : nums) {
      if (num) {
        ++windowSize;
      }
    }

    int maxInWindow = 0;
    int inWindow = 0;

    int l = 0;
    for (int r = 0; r < n + windowSize - 1; ++r) {
      if (nums[r % n]) {
        // consider the element at the right of the window
        ++inWindow;
      }

      if (r - l + 1 > windowSize) {
        if (nums[l++]) {
          --inWindow;
        }
      }

      maxInWindow = std::max(maxInWindow, inWindow);
    }

    return windowSize - maxInWindow;
  }
};
