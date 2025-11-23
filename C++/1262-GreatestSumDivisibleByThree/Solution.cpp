#include <algorithm>
#include <array>
#include <vector>

class Solution {
 public:
  int maxSumDivThree(std::vector<int>& nums) {
    // Return the maximum possible sum of elements of the array such that it
    // is divisible by three.
    //
    // - A number divisible by three can trivially be included.
    // - remainder of 1 => need a remainder of 3 to balance out, and vice-versa.
    // Greedily pick the largest of each.
    // Seems like two-pass + sorting?
    //
    // Nope. Does not work.
    // Two remainder-2 and One remainder-1 produces a sum divisible by 3.
    // E.g., 4+4+1
    // There are multiple such combinations.
    //
    // Consider 3-state DP.
    // dp[0] = largest sum that is divisible by 3
    // dp[1] = largest sum that gives a remainder of 1
    // dp[2] = largest sum that gives a remainder of 2
    // Then, at each index i, r = nums[i]%3. If r is 0, then dp[0] += nums[i].
    // For dp[1] and dp[2], add nums[i] and update respectively.
    const auto n = static_cast<int>(nums.size());

    std::array<int, 3> dp{};
    for (auto x : nums) {
      for (auto psum : std::array{dp}) {
        auto remainder = (psum + x) % 3;
        dp[remainder] = std::max(dp[remainder], psum + x);
      }
    }
    return dp[0];
  }
};
