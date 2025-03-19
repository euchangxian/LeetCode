#include <vector>

class Solution {
 public:
  int minOperations(std::vector<int>& nums) {
    // Similar to first variant, but flip suffix. We can maintain a running
    // variable to determine lazily how many times to flip the current bit.
    const int n = nums.size();
    int ops = 0;
    bool flip = 0;
    for (int i = 0; i < n; ++i) {
      if ((nums[i] ^ flip) == 0) {
        ++ops;
        flip = !flip;
        nums[i] = 1;
      }
    }

    return ops;
  }
};
