#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maxDistinctElements(std::vector<int>& nums, int k) {
    // given k, perform the operation on EACH element at MOST once:
    // add an integer x, -k <= x <= k to the element.
    // Return the maximum number of distinct elements.
    // Hm. Feels like sorting and greedily applying the operation.
    // This is done by setting each element to its minimum.
    // Visualize a sort of vertical window when iterating.
    // This vertical window represents [nums[i] - k, nums[i] + k]
    // Thus, by greedily setting to the minimum possible
    std::sort(nums.begin(), nums.end());

    int distinct = 0;
    int previous = INT_MIN;
    for (int num : nums) {
      int lower = num - k;
      int upper = num + k;

      // Can trivially set to the minimum element.
      if (previous < lower) {
        ++distinct;
        previous = lower;
        continue;
      }

      // otherwise, check if the previous minimum has exceeded the current's
      // upper bound. If not, then we can take previous + 1.
      // This is because we have already sorted the input.
      if (previous < upper) {
        ++distinct;
        previous = previous + 1;
      }
    }
    return distinct;
  }
};
