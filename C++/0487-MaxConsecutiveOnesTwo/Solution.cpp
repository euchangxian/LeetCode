#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int findMaxConsecutiveOnes(std::vector<int>& nums) {
    // Maximum consecutive '1's in the array if only one zero can be flipped.
    // Max length sliding window with at most one 1.
    // For the followup, i think its segment tree.
    int best = 0;

    int zeroes = 0;
    int l = 0;
    for (int r = 0; r < nums.size(); ++r) {
      zeroes += nums[r] == 0;
      while (zeroes > 1 && l < r) {
        zeroes -= nums[l] == 0;
        ++l;
      }

      best = std::max(best, r - l + 1);
    }
    return best;
  }
};
