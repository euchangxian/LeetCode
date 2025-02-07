#include <algorithm>
#include <string_view>
#include <vector>

class Solution {
 public:
  int longestCommonSubsequence(std::string_view s1, std::string_view s2) {
    int m = s1.length();
    int n = s2.length();

    // After the ith iteration, dp[j] represents the
    // LCS of s1[:i] and s2[:j] (slicing syntax, exclusive)
    std::vector<int> dp(n + 1, 0);

    // dp[0][j] = 0 for all j.
    // dp[i][0] = 0 for all i.

    for (int i = 1; i <= m; ++i) {
      std::vector<int> curr = dp;
      for (int j = 1; j <= n; ++j) {
        // 1-indexed to 0-indexed
        if (s1[i - 1] == s2[j - 1]) {
          // dp[i-1][j-1] + 1
          curr[j] = dp[j - 1] + 1;
        } else {
          // Max of dp[i-1][j], dp[i][j-1]
          curr[j] = std::max(dp[j], curr[j - 1]);
        }
      }
      dp = std::move(curr);
    }
    return dp[n];
  }
};
