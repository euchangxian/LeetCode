#include <algorithm>
#include <vector>

class Solution {
 public:
  int longestNiceSubarray(std::vector<int>& nums) {
    // A subarray is nice IF the bitwise AND of every pair of elements
    // is equal to 0.
    // Return length of longest nice subarray.
    //
    // If two elements do not share 1s in the same position, then their & is 0.
    //
    // Feels like sliding window. But for a new element, how to check against
    // every existing pair in the subarray efficiently?
    // Similarly, when removing an element, how to check?
    //
    // Most naively, a Map for each of the 32 positions in an integer, where an
    // element will be inserted into the map if it has a set bit in that
    // position.
    // Thus, we want to ensure each bucket contains only 1 element.
    // Ah. We can maintain a mask then.
    // Sliding window with a mask.
    int best = 0;
    int mask = 0;
    int l = 0;
    for (int r = 0; r < nums.size(); ++r) {
      while (mask & nums[r]) {
        mask ^= nums[l++];
      }
      mask |= nums[r];
      best = std::max(best, r - l + 1);
    }
    return best;
  }
};
