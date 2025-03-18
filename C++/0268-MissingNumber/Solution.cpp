#include <vector>

class Solution {
 public:
  int missingNumber(std::vector<int>& nums) {
    int n = nums.size();
    int missing = 0;
    for (int i = 0; i < n; ++i) {
      // The key is:
      // A XOR A = 0
      // B XOR 0 = B
      // So in a array where there are no missing numbers from 0 to n,
      // there will always be a pair of index i and nums[i]
      // such that i == nums[i]
      missing = missing ^ i ^ nums[i];
    }

    return missing ^ n;
  }
};
