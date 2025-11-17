#include <utility>
#include <vector>

class Solution {
 public:
  bool kLengthApart(std::vector<int>& nums, int k) {
    // Return true if all 1s are at least k places away from each other.
    int count = k;  // first 0
    for (int x : nums) {
      if (x == 1) {
        if (std::exchange(count, 0) < k) {
          return false;
        }
      } else {
        ++count;
      }
    }
    return true;
  }
};
