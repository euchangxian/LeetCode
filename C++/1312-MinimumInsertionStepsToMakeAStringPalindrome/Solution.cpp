#include <algorithm>
#include <array>
#include <string_view>
#include <utility>

constexpr int MAX_N = 500;
class Solution {
 public:
  int minInsertions(std::string_view s) {
    // Given that we can insert at any point in the string, we can find the
    // Longest Palindromic Subsequence of the string s (which is just the
    // LCS of s and its reverse).
    // After which, the number of characters will just be s.length - lps
    const int n = s.size();
    int lps = longestPalindromicSubsequence(s);
    return n - lps;
  }

 private:
  int longestPalindromicSubsequence(std::string_view s) {
    const int n = s.size();

    std::array<int, MAX_N> prev{}, dp{};
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
};
