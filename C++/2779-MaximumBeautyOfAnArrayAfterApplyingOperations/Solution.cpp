#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maximumBeauty(std::vector<int>& nums, int k) {
    // Had to see the hints.
    // First, note that the original ordering of nums is unimportant.
    // We only want the longest subsequence. Operations depend on the element
    // itself.
    // We want elements that are within a range. E.g.,
    // every element in nums[i..j] should be within the range of -k and k, i.e.,
    // max(nums[i..j]) - min(nums[i..j]) <= 2k.
    // Sorting the array would let us figure that out!! This is quite an elegant
    // reduction of the problem into a sliding window one, where we want to find
    // the maximum subarray such that the leftmost element of the window,
    // nums[r] - nums[l] <= 2k.
    std::sort(nums.begin(), nums.end());

    int maxLength = 0;
    int l = 0;
    for (int r = 0; r < nums.size(); ++r) {
      while (l < r && nums[r] - nums[l] > 2 * k) {
        ++l;
      }
      maxLength = std::max(maxLength, r - l + 1);
    }
    return maxLength;
  }
};
