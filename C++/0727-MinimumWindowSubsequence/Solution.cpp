#include <algorithm>
#include <climits>
#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  std::string minWindow(std::string_view s, std::string_view t) {
    const int m = s.size();
    const int n = t.size();

    // dp[i][j] = starting index of the subsequence ending at i that matches
    // t[0...j-1]
    // Note bottom-up is STARTING index.
    // Note the transposition. Since we will be traversing over t, then s,
    // transposing will provide better cache performance.
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, -1));
    for (int i = 0; i <= m; ++i) {
      dp[0][i] = i;  // matching empty substring is trivially possible.
    }

    for (int j = 1; j <= n; ++j) {
      for (int i = 1; i <= m; ++i) {
        if (t[j - 1] == s[i - 1]) {
          dp[j][i] = dp[j - 1][i - 1];
        } else {
          dp[j][i] = dp[j][i - 1];
        }
      }
    }

    int minLeft = INT_MAX;
    int minLength = INT_MAX;
    for (int i = 1; i <= m; ++i) {
      if (dp[n][i] != -1 && i - dp[n][i] < minLength) {
        minLength = i - dp[n][i];
        minLeft = dp[n][i];
      }
    }

    if (minLength == INT_MAX) {
      return "";
    }
    return std::string{s.substr(minLeft, minLength)};
  }

  std::string minWindowTopDown(std::string_view s, std::string_view t) {
    // How is this different from 76. Minimum Window Substring, where
    // given s and t, return the minimum substring of s that contains every
    // character of t.
    // Ah. This has a stricter requirement of being a subsequence, not just
    // a rearrangement of t.
    //
    // Hm. Sliding window seems possible. Two pointers on s for the window,
    // two pointers on t for the subsequence covered.
    // Hm not really too.
    // When a valid subsequence is found, shrinking the window is non-trivial.
    // Need to keep track of frequency? Not trivial too.
    //
    // Naively, find the LCS at each starting index of s. If the subsequence
    // is equal to t, then we found a valid answer.
    // O(n * nm)
    // Feels like theres plenty of recomputed work, where we can optimize this
    // with DP. Just not sure how.
    // Though, given the constraints s.length <= 10^4, t.length <= 100,
    // it is possible to AC.
    const int m = s.size();
    const int n = t.size();
    int minLeft = INT_MAX;
    int minLength = INT_MAX;

    // dp[i][j] represents the ending index in s for the subsequence that starts
    // at index i, and contains the subsequence of t[..j]
    std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
    dfs(s, t, memo, 0, 0, minLeft, minLength);

    if (minLength == INT_MAX) {
      return "";
    }
    return std::string{s.substr(minLeft, minLength)};
  }

 private:
  int dfs(std::string_view s,
          std::string_view t,
          std::vector<std::vector<int>>& memo,
          int i,
          int j,
          int& minLeft,
          int& minLength) {
    if (j >= t.size()) {
      return i;
    }

    if (i >= s.size()) {
      return INT_MAX;  // not possible.
    }

    int& ans = memo[i][j];
    if (ans != -1) {
      return ans;
    }

    int match = INT_MAX;
    int skip = INT_MAX;
    if (s[i] == t[j]) {
      match = dfs(s, t, memo, i + 1, j + 1, minLeft, minLength);
    }
    skip = dfs(s, t, memo, i + 1, j, minLeft, minLength);

    ans = std::min(match, skip);

    // NOTE: since the recursion call unrolls from rightmost i to leftmost,
    // we want to use '<=' instead of '<', to get the leftmost i as required.
    // Also, note that ans=min(match, skip) will be 1-indexed, since the
    // previous recursive call would have involved i+1.
    // Thus, ans-i gives the length.
    if (j == 0 && ans != INT_MAX && ans - i <= minLength) {
      minLeft = i;
      minLength = ans - i;
    }

    return ans;
  }
};
