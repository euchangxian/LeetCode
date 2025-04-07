#include <bitset>
#include <functional>
#include <numeric>
#include <vector>

constexpr int MAX_N = 200;
constexpr int MAX_VAL = 100;
class Solution {
 public:
  bool canPartition(std::vector<int>& nums) {
    // Looks like binary search. Threshold would be half of the total sum.
    // Possibly DP, since at each element, there are two choices:
    // 1. Take the element, add its sum into the current subset
    // 2. Skip the element.
    // To find a subset sum equal to k, where k is half the total sum.
    // Possibly formulate it as dp[i], 1 <= 2 * k, dp[i] represents whether
    // it is possible to create a subset of sum i

    const int sum = std::reduce(nums.begin(), nums.end(), 0, std::plus<>{});

    // if the sum is odd, then there is no way to partition into two equal
    // subsets
    if (sum % 2 != 0) {
      return false;
    }
    const int k = sum / 2;

    std::bitset<MAX_N * MAX_VAL + 1> dp{};
    dp[0] = true;
    // Similar to coin change. BUT, iterate over the coins in the outer loop
    // to ensure each coin is taken at MOST once.
    for (int num : nums) {
      // IMPORTANT: we iterate backwards so that results from earlier iteration
      // will not affect the current iteration. Emulates a temporary array.
      // E.g., if num=1, and we iterate from the start, its akin to taking
      // multiple copies of 1.
      for (int amt = k; amt >= num; --amt) {
        dp[amt] = dp[amt] | dp[amt - num];
      }
    }
    return dp[k];
  }

  bool canPartitionMemo(std::vector<int>& nums) {
    // dfs(i, sum) =
    //    dfs(i+1, sum) // skip
    // || dfs(i+1, sum-nums[i]) // take
    const int n = nums.size();
    int sum = std::reduce(nums.begin(), nums.end(), 0, std::plus<>{});
    if (sum % 2 != 0) {
      return false;
    }

    int k = sum / 2;
    std::vector<std::vector<int>> memo(n, std::vector<int>(k + 1, -1));
    return dfs(nums, memo, 0, k);
  }

  bool dfs(std::vector<int>& nums,
           std::vector<std::vector<int>>& memo,
           int i,
           int k) {
    if (k <= 0) {
      return k == 0;
    }

    if (i >= nums.size()) {
      return false;
    }

    int& ans = memo[i][k];
    if (ans != -1) {
      return ans;
    }

    return ans =
               dfs(nums, memo, i + 1, k) || dfs(nums, memo, i + 1, k - nums[i]);
  }
};
