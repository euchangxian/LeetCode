#include <vector>

class Solution {
 public:
  bool canJump(std::vector<int>& nums) {
    int n = nums.size();
    int jumps = 1;
    int furthest = nums[0];  // Represents the furthest index reachable
    for (int i = 1; i < n; ++i) {
      if (i > furthest) {
        return false;
      }

      if (i + nums[i] > furthest) {
        furthest = i + nums[i];
      }

      if (furthest >= n - 1) {
        break;
      }
    }
    return true;
  }
};
