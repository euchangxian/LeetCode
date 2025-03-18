#include <climits>
#include <cstddef>
#include <functional>
#include <numeric>
#include <vector>

class Solution {
 public:
  int findTargetSumWays(const std::vector<int>& nums, const int target) {
    const size_t n{nums.size()};
    const int offset{std::reduce(nums.begin(), nums.end(), 0, std::plus<>{})};

    if (std::abs(target) > offset) {
      return 0;
    }

    // dp[i][j] represents the number of ways to make up the target j with
    // the first i nums
    std::vector<std::vector<int>> dp(n, std::vector<int>(2 * offset + 1, 0));
    dp[0][nums[0] + offset] = 1;

    // NOTE the +=. To deal with cases where nums[0] is 0
    dp[0][-nums[0] + offset] += 1;

    for (size_t i{1}; i < n; ++i) {
      // for each sum
      for (int sum{-offset}; sum <= offset; ++sum) {
        if (dp[i - 1][sum + offset] > 0) {
          dp[i][sum + offset + nums[i]] += dp[i - 1][sum + offset];
          dp[i][sum + offset - nums[i]] += dp[i - 1][sum + offset];
        }
      }
    }

    return dp[n - 1][target + offset];
  }

  int findTargetSumWays(std::vector<int>& nums, int target) {
    // First glance looked like DFS.
    // Notice that there is quite abit of repeated work. Specifically,
    // when considering a new element i, the sum of the first i-1
    // elements +- i could be equal to the target.
    constexpr int MAX_SUM = 1000;
    constexpr int OFFSET = MAX_SUM;  // -1000 <= target <= 1000

    // After the ith iteration, let dp[j] represent the number of ways to make
    // up the sum j using the first i elements.
    std::array<int, 2 * MAX_SUM + 1> dp{};
    dp[nums[0] + OFFSET] = 1;
    dp[-nums[0] + OFFSET] += 1;  // nums[0] could be 0, thus the +=
    for (int i = 1; i < nums.size(); ++i) {
      std::array<int, 2 * MAX_SUM + 1> next{};
      for (int sum = -MAX_SUM; sum <= MAX_SUM; ++sum) {
        if (sum + nums[i] <= MAX_SUM) {
          next[sum + nums[i] + OFFSET] += dp[sum + OFFSET];
        }
        if (sum - nums[i] >= -MAX_SUM) {
          next[sum - nums[i] + OFFSET] += dp[sum + OFFSET];
        }
      }
      dp = std::move(next);
    }

    return dp[target + OFFSET];
  }

  int findTargetSumWaysMemo(std::vector<int>& nums, int target) {
    // Two choices at each element. Add or minus
    // Naive DFS can do it. Reduces to backtracking problem for subsequence
    // sum equal to k
    // 0 <= nums[i], sum(nums[i]) <= 1000
    // -1000 <= target <= 1000
    const int sum = std::reduce(nums.begin(), nums.end(), 0, std::plus<>{});
    offset = sum;

    // negative to positive sum + 1 for the zero.
    std::vector<std::vector<int>> memo(nums.size(),
                                       std::vector<int>(2 * sum + 1, INT_MIN));

    return dfs(memo, nums, target, 0, 0);
  }

 private:
  // Sum of the elements in nums.
  int offset;

  int dfs(std::vector<std::vector<int>>& memo,
          const std::vector<int>& nums,
          const int target,
          size_t idx,
          int sum) {
    if (idx >= nums.size()) {
      if (sum == target) {
        return 1;
      }
      return 0;
    }

    if (memo[idx][sum + offset] != INT_MIN) {
      return memo[idx][sum + offset];
    }

    int subtract = dfs(memo, nums, target, idx + 1, sum - nums[idx]);
    int add = dfs(memo, nums, target, idx + 1, sum + nums[idx]);

    memo[idx][sum + offset] = add + subtract;
    return memo[idx][sum + offset];
  }
};
