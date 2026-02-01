#include <algorithm>
#include <vector>

class Solution {
 public:
  int minimumCost(std::vector<int>& nums) {
    // cost of array is the value of its first element.
    // Divide nums into 3 disjoint, contiguous subarrays.
    // Return the minimum possible sum of cost.
    //
    // Enumeration works. Can we do better?
    // Can just pick the smallest-3.
    // Oh. First element must always be included.
    std::nth_element(nums.begin() + 1, nums.begin() + 3, nums.end());
    return nums[0] + nums[1] + nums[2];
  }
};
