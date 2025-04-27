#include <vector>

class Solution {
 public:
  int countSubarrays(std::vector<int>& nums) {
    // Count subarrays of length 3 such that the sum of the first and third
    // number is exactly half of the second.
    int count = 0;
    for (int i = 1; i < nums.size() - 1; ++i) {
      count += (nums[i - 1] + nums[i + 1]) * 2 == nums[i];
    }
    return count;
    // NOTE: std::ranges::slide is not yet implemented in clangd as 27/04/25
    // return std::ranges::distance(nums | std::ranges::views::slide(3) |
    //                              std::ranges::views::filter([](auto window) {
    //                                return (window[0] + window[2]) * 2 ==
    //                                       window[1];
    //                              }));
  }
};
