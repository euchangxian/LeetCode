#include <algorithm>
#include <array>
#include <vector>

constexpr int MAX_N = 1000;
constexpr int MAX_NUM = 500;  // Also the offset, i.e., 0-500 is -500, negative.

class Solution {
 public:
  int longestArithSeqLength(std::vector<int>& nums) {
    const int n = nums.size();

    int result = 2;

    // dp[i][j] represents the longest arithmetic sequence ending at index i
    // with difference j.
    std::array<std::array<int, 2 * MAX_NUM + 1>, MAX_N> dp;
    std::fill(dp[0].begin(), dp[0].end(), 1);

    for (int i = 1; i < n; ++i) {
      std::fill(dp[i].begin(), dp[i].end(), 1);
      for (int j = 0; j < i; ++j) {
        int diff = nums[i] - nums[j] + MAX_NUM;
        dp[i][diff] = dp[j][diff] + 1;
        result = std::max(result, dp[i][diff]);
      }
    }
    return result;
  }
};
