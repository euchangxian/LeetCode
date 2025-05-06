#include <vector>

class Solution {
 public:
  std::vector<int> buildArray(std::vector<int>& nums) {
    // ans[i] = nums[nums[i]]
    // Trivial with extra space. O(1) space?
    // Can do O(N^2) with O(1) space, by selecting the max valued nums[i].
    // Can we do better?
    const int n = nums.size();
    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
      result[i] = nums[nums[i]];
    }
    return result;
  }
};
