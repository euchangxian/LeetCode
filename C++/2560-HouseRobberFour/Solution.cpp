#include <algorithm>
#include <vector>

class Solution {
 public:
  int minCapability(std::vector<int>& nums, int k) {
    // Cannot rob adjacent houses.
    // Capability of the robber is the maximum amount of money stolen.
    // Must rob at least k houses (always possible).
    // Minimum capability out of the different possible ways to rob at least k
    // houses.
    // Not the kth largest nums[i]. More like the kth largest path.
    // Clearly naive DFS would not work with this constraint.
    auto feasible = [k, &nums](int max) -> bool {
      int robbed = 0;
      for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] <= max) {
          ++robbed;
          ++i;  // skip next to maintain non-adjacent requirement.
        }
      }
      return robbed >= k;
    };

    auto [min, max] = std::minmax_element(nums.begin(), nums.end());
    int left = *min;
    int right = *max;
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (feasible(mid)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};
