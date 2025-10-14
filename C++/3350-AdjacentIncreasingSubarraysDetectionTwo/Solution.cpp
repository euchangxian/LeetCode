#include <algorithm>
#include <utility>
#include <vector>

class Solution {
 public:
  int maxIncreasingSubarrays(std::vector<int>& nums) {
    const auto n = static_cast<int>(nums.size());
    int curr = 1;
    int prev = 0;
    int result = 0;
    for (int i = 1; i < n; ++i) {
      if (nums[i] > nums[i - 1]) {
        ++curr;
      } else {
        prev = std::exchange(curr, 1);
      }

      result = std::max({result, curr / 2, std::min(prev, curr)});
    }
    return result;
  }
};
