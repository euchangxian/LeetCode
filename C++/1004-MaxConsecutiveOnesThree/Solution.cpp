#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int longestOnes(std::vector<int>& nums, int k) {
    int l = 0;
    int r = 0;
    for (; r < nums.size(); ++r) {
      k -= nums[r] == 0;

      // Note that l is always incremented if k < 0, regardless if whether
      // nums[l] is zero or not.
      if (k < 0 && nums[l++] == 0) {
        ++k;
      }
    }

    return r - l;
  }
};
