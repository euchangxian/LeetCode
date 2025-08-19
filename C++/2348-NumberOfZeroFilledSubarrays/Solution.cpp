#include <vector>

using i64 = long long;

class Solution {
 public:
  i64 zeroFilledSubarray(std::vector<int>& nums) {
    // Return the number of non-empty subarrays filled with 0.
    // Sliding Window/2-pointer
    i64 result = 0;
    int i = 0;
    while (i < nums.size()) {
      if (nums[i] != 0) {
        ++i;
        continue;
      }

      i64 zeroes = 0;
      while (i < nums.size() && nums[i] == 0) {
        ++zeroes;
        result += zeroes;
        ++i;
      }
    }
    return result;
  }
};
