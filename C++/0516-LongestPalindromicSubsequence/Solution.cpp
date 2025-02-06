#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  int longestPalindromeSubseq(std::string s) {
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
