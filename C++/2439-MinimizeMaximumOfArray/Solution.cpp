#include <algorithm>
#include <vector>

class Solution {
 public:
  int minimizeArrayValue(std::vector<int>& nums) {
    // Given n non-negative integers. In one operation, choose an index i such
    // that:
    // - decrease nums[i] by 1
    // - increase nums[i-1] by 1.
    // Return the minimum possible value of the maximum integer of nums after
    // performing any number of operations.
    //
    // Note that we are "moving" values backwards.
    long long result = 0;
    long long prefix = 0;
    for (int i = 0; i < nums.size(); ++i) {
      prefix += nums[i];

      // ceiling div over number of prefix elements.
      result = std::max(result, (prefix + i) / (i + 1));
    }
    return result;
  }
};
