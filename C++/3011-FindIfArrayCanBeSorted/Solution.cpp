#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

using namespace std;
class Solution {
 public:
  bool canSortArray(std::vector<int>& nums) {
    // Allowed to swap adjacent elements if they have the same number of '1'
    // bits.
    // Hm. Naively checking if EVERY element has the same number of '1' bits
    // would not work, since there could be a case where the array is already
    // partially sorted, and only one pair of elements need to be swapped.
    // Though it seems that nums.length <= 100 indicate an exponential runtime.
    // Maybe we can preprocess the nums array to figure out the number of set
    // bits of each element.
    // Then, determine the sorted position of each element. (HOW?)
    // This allows to to know which elements need to be swapped based on the
    // elements between the actual and expected index.
    // Hmmmm. Observe that we can "partition" the nums array into contiguous
    // subarrays where each element have the same number of set bits.
    // Therefore, for each of the subarrays, the elements within can be sorted
    // using the operations.
    // Then, for adjacent subarrays, if the maximum of the left subarray is
    // smaller than the minimum of the right subarray, then we know that the
    // combined subarray can be sorted.
    const size_t n = nums.size();

    // maintain min/max of current segment
    int currMin = nums[0];
    int currMax = nums[0];

    // max of previous segment
    int prevMax = -1;

    for (int i = 1; i < nums.size(); ++i) {
      // check if the number belongs to the current segment
      if (__builtin_popcount(nums[i]) == __builtin_popcount(currMin)) {
        currMin = std::min(currMin, nums[i]);
        currMax = std::max(currMax, nums[i]);
        continue;
      }

      // Otherwise, we are in a new segment.
      // Check that the current (the segment we just passed), whether its min
      // is greater than the previous segment
      if (currMin < prevMax) {
        return false;
      }

      prevMax = currMax;

      // start a new segment!
      currMin = nums[i];
      currMax = nums[i];
    }

    return currMin >= prevMax;
  }
};
