#include <numeric>
#include <vector>

class Solution {
 public:
  int countMaxOrSubsets(const std::vector<int>& nums) {
    constexpr int kMaxOR = 2 << 17;  // 10^5 => 17 bits required
    std::array<int, kMaxOR> dp{};
    // base case, empty subset
    dp[0] = 1;

    int currMaxOR = 0;
    for (const int num : nums) {
      // iterator from the back to prevent earlier iterations from affecting
      // subsequent results. Avoids the use of a temp array.
      for (int i = currMaxOR; i >= 0; --i) {
        // For each subset with an OR sum of i, add num to it.
        dp[i | num] += dp[i];
      }
      currMaxOR |= num;  // No need for std::max with bitwise OR
    }

    return dp[currMaxOR];
  }

  int countMaxOrSubsetsMemo(const std::vector<int>& nums) {
    int maxOR = std::reduce(nums.begin(), nums.end(), 0,
                            [](const int& a, const int& b) { return a | b; });

    std::vector<std::vector<int>> memo(nums.size(),
                                       std::vector<int>(maxOR + 1, 0));
    return dfs(nums, memo, maxOR, 0, 0);
  }

 private:
  int dfs(const std::vector<int>& nums,
          std::vector<std::vector<int>>& memo,
          const int& maxOR,
          int currOR,
          int idx) {
    if (idx >= nums.size()) {
      return (currOR == maxOR);
    }

    if (memo[idx][currOR]) {
      return memo[idx][currOR];
    }

    int take = dfs(nums, memo, maxOR, currOR | nums[idx], idx + 1);
    int skip = dfs(nums, memo, maxOR, currOR, idx + 1);

    memo[idx][currOR] = take + skip;
    return memo[idx][currOR];
  }
};
