#include <algorithm>
#include <climits>
#include <vector>

class Solution {
 public:
  int minDifference(std::vector<int>& nums) {
    if (nums.size() <= 4) {
      return 0;
    }
    std::sort(nums.begin(), nums.end());

    // Three moves => 4 combinations
    // Increase first three numbers
    // Increase first two, decrease last
    // Increase first, decrease last 2
    // Decrease last three numbers
    int left = 0;
    int right = nums.size() - 4;

    int minDiff = INT_MAX;
    // four scenarios, i.e. left moves up to 4th element
    while (left < 4) {
      minDiff = std::min(minDiff, nums[right++] - nums[left++]);
    }
    return minDiff;
  }
};
