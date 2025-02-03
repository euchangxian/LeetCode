#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int longestMonotonicSubarray(std::vector<int>& nums) {
    int longest = 1;
    int incr = 1;
    int decr = 1;
    int curr = 1;
    for (int i = 1; i < nums.size(); ++i) {
      incr = nums[i - 1] < nums[i] ? incr + 1 : 1;
      decr = nums[i - 1] > nums[i] ? decr + 1 : 1;
      longest = std::max({longest, incr, decr});
    }
    return longest;
  }
};
