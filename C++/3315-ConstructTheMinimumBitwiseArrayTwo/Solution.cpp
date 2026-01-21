#include <vector>

class Solution {
 public:
  std::vector<int> minBitwiseArray(std::vector<int>& nums) {
    // Given n prime integers nums.
    // construct ans of length n such that for each index i,
    // ans[i]|(ans[i]+1) == nums[i].
    // Minimise ans[i].
    const auto n = static_cast<int>(nums.size());
    std::vector<int> ans;
    ans.reserve(n);
    for (auto num : nums) {
      if (num == 2) {
        ans.push_back(-1);
      } else {
        // tail mask
        auto mask = ((num + 1) & ~num) >> 1;
        ans.push_back(num ^ mask);
      }
    }
    return ans;
  }
};
