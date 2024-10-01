#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
private:
  // Sum of the elements in nums.
  int offset;

  int dfs(vector<vector<int>> &memo, const vector<int> &nums, const int target,
          size_t idx, int sum) {
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

public:
  int findTargetSumWays(const vector<int> &nums, const int target) {
    const size_t n{nums.size()};
    const int offset{std::reduce(nums.begin(), nums.end(), 0, plus<>{})};

    if (std::abs(target) > offset) {
      return 0;
    }

    // dp[i][j] represents the number of ways to make up the target j with
    // the first i nums
    vector<vector<int>> dp(n, vector<int>(2 * offset + 1, 0));
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

  int findTargetSumWaysMemo(vector<int> &nums, int target) {
    // Two choices at each element. Add or minus
    // Naive DFS can do it. Reduces to backtracking problem for subsequence
    // sum equal to k
    // 0 <= nums[i], sum(nums[i]) <= 1000
    // -1000 <= target <= 1000
    const int sum = std::reduce(nums.begin(), nums.end(), 0, plus<>{});
    offset = sum;

    // negative to positive sum + 1 for the zero.
    vector<vector<int>> memo(nums.size(), vector<int>(2 * sum + 1, INT_MIN));

    return dfs(memo, nums, target, 0, 0);
  }
};
