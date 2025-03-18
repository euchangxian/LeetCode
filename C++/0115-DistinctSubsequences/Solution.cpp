#include <climits>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

class Solution {
 private:
  int dfs(std::vector<std::vector<int>>& memo,
          std::string_view s,
          std::string_view t,
          std::size_t i,
          std::size_t j) {
    // check that j is also at the end
    if (j >= t.length()) {
      return 1;
    }

    if (i >= s.length()) {
      return 0;
    }

    if (memo[i][j] != INT_MIN) {
      return memo[i][j];
    }

    int count = dfs(memo, s, t, i + 1, j);

    if (s[i] == t[j]) {
      count += dfs(memo, s, t, i + 1, j + 1);
    }

    memo[i][j] = count;
    return count;
  }

 public:
  int numDistinct(std::string s, std::string t) {
    const size_t m(s.length());
    const size_t n(t.length());

    // std::vector<std::vector<int>> memo(m, std::vector<int>(n, INT_MIN));
    // return dfs(memo, s, t, 0, 0);

    // dp[i][j] represents the number of distinct subsequences of s[:i] which
    // equal to t[:j]
    std::vector<std::vector<uint64_t>> dp(m + 1,
                                          std::vector<uint64_t>(n + 1, 0));
    for (int i = 0; i <= m; ++i) {
      dp[i][0] = 1;  // any pattern of length 0 is vacuously true
    }

    for (std::size_t i = 1; i <= m; ++i) {
      for (std::size_t j = 1; j <= n; ++j) {
        dp[i][j] = dp[i - 1][j];  // no match

        if (s[i - 1] == t[j - 1]) {
          dp[i][j] += dp[i - 1][j - 1];
        }
      }
    }
    return dp[m][n];
  }
};
