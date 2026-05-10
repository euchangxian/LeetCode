#include <algorithm>
#include <cmath>
#include <vector>

class Solution {
 public:
  int maximumJumps(std::vector<int>& nums, int target) {
    // Start at index 0, jump from index i to any index j such that:
    // - 0 <= i < j < n,
    // - -target <= nums[j] - nums[i] <= target
    // Return the maximum number of jumps to reach index n-1, or -1.
    //
    // - Can only jump forward
    // - abs(nums[i] - nums[j]) <= target.
    // Seems like search?
    // Maximum => jump as small as possible?
    //
    // dp[i] => maximum number of jumps to reach the i-th index?
    // dp[j] = std::max{dp[j], dp[i]+1 if (nums[i]-nums[j] <= target)}
    const auto n = static_cast<int>(nums.size());

    std::vector<int> dp(n, -1);
    dp[0] = 0;
    for (int j = 1; j < n; ++j) {
      for (int i = 0; i < j; ++i) {
        if (dp[i] == -1) {
          continue;
        }
        if (std::abs(nums[i] - nums[j]) <= target) {
          dp[j] = std::max(dp[j], dp[i] + 1);
        }
      }
    }

    return dp[n - 1];
  }
};
