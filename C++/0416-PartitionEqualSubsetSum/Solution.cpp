#include <functional>
#include <vector>

using namespace std;
class Solution {
 public:
  bool canPartition(vector<int>& nums) {
    // Looks like binary search. Threshold would be half of the total sum.
    // Possibly DP, since at each element, there are two choices:
    // 1. Take the element, add its sum into the current subset
    // 2. Skip the element.
    // To find a subset sum equal to k, where k is half the total sum.
    // Possibly formulate it as dp[i], 1 <= 2 * k, dp[i] represents whether
    // it is possible to create a subset of sum i

    const int32_t sum = std::reduce(nums.begin(), nums.end(), 0, std::plus<>{});

    // if the sum is odd, then there is no way to partition into two equal
    // subsets
    if (sum & 1) {
      return false;
    }

    const int32_t k = sum / 2;
    std::vector<bool> dp(k + 1, false);
    dp[0] = true;

    // Similar to coin change. BUT, iterate over the coins in the outer loop
    // to ensure each coin is taken at MOST once.
    for (const int& num : nums) {
      // IMPORTANT: we iterate backwards so that results from earlier iteration
      // will not affect the current iteration. Emulates a temporary array.
      // E.g., if num=1, and we iterate from the start, its akin to taking
      // multiple copies of 1.
      for (size_t amt = k; amt >= num; --amt) {
        dp[amt] = dp[amt] || dp[amt - num];
      }
    }
    return dp[k];
  }
};
