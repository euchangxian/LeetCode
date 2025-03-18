#include <algorithm>
#include <vector>

class Solution {
 public:
  int rob(std::vector<int>& nums) {
    int currMax = 0;
    int prevMax = 0;

    for (int num : nums) {
      int newMax = std::max(currMax, prevMax + num);

      prevMax = currMax;
      currMax = newMax;
    }
    return currMax;
  }
};
