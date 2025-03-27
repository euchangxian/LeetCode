#include <algorithm>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

constexpr int MAX_N = 1000;
class Solution {
 public:
  int longestPalindromeSubseq(std::string_view s) {
    const int n = s.size();

    std::array<int, MAX_N> prev{};
    std::array<int, MAX_N> dp{};

    for (int i = n - 1; i >= 0; --i) {
      dp[i] = 1;
      for (int j = i + 1; j < n; ++j) {
        if (s[i] == s[j]) {
          dp[j] = 2 + prev[j - 1];
        } else {
          dp[j] = std::max(dp[j - 1], prev[j]);
        }
      }
      prev = std::move(dp);
    }
    return dp[n - 1];
  }

  int longestPalindromeSubseq2D(std::string_view s) {
    const int n = s.size();

    // Consider (i, j), starting from the beginning and the end.
    // dp[i][j] = dp[i+1][j-1] + 2            if s[i] == s[j]
    // dp[i][j] = max(dp[i+1][j], dp[i][j-1]) otherwise.
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    // consider substrings, s[i:j]
    // The order of iteration is weird. But consider the recursive top-down
    // approach, where dp[i+1] need to be computed before dp[i], and
    // dp[i][j-1] need to be computed before dp[i][j].
    for (int i = n - 1; i >= 0; --i) {
      dp[i][i] = 1;
      for (int j = i + 1; j < n; ++j) {
        if (s[i] == s[j]) {
          dp[i][j] = 2 + dp[i + 1][j - 1];
        } else {
          dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
        }
      }
    }
    return dp[0][n - 1];
  }

  int longestPalindromeSubseqLCS(std::string s) {
    // Longest Palindrome Subsequence of a string is just the Longest Common
    // Subsequence of the string and its reverse.
    std::string t{s.rbegin(), s.rend()};
    return longestCommonSubsequence(s, t);
  }

 private:
  int longestCommonSubsequence(std::string_view s, std::string_view t) {
    const int n = s.size();
    const int m = t.size();

    // dp[j] represents LCS(s[:i], t), i.e., the longest common subsequence of
    // the first i characters of s and the first j characters of j.
    // dp[0][j] = 0
    // dp[i][0] = 0
    std::vector<int> dp(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
      std::vector<int> curr(m + 1, 0);
      for (int j = 1; j <= m; ++j) {
        if (s[i - 1] == t[j - 1]) {
          // dp[i-1][j-1]
          curr[j] = dp[j - 1] + 1;
        } else {
          // max{dp[i-1][j], dp[i][j-1]}
          curr[j] = std::max(dp[j], curr[j - 1]);
        }
      }
      dp = std::move(curr);
    }
    return dp.back();
  }
};
