#include <vector>

class Solution {
 public:
  int minOperations(std::vector<int>& nums) {
    // Any number of times:
    // - Choose any 3 consecutive elements, flip all of them.
    // Return minimum number of operations.
    // Typically for these kind of questions, need to simplify the operation?
    // Suppose we have a 0-bit.
    // Let this bit be M, the bits to the right be R1, R2.
    // If R1=0,R2=0, we are done.
    // Hm. Just greedily simulate. Lol.
    const int n = nums.size();
    int ops = 0;
    for (int i = 0; i + 2 < nums.size(); ++i) {
      if (nums[i] == 0) {
        ++ops;
        nums[i] = 1;
        nums[i + 1] = 1 - nums[i + 1];
        nums[i + 2] = 1 - nums[i + 2];
      }
    }

    return (nums[n - 2] == 1 && nums[n - 1] == 1) ? ops : -1;
  }
};
