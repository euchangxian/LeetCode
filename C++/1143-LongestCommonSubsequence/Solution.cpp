#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 public:
  int longestCommonSubsequence(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();

    // After the ith iteration, dp[j] represents the
    // LCS of s1[:i] and s2[:j] (slicing syntax, exclusive)
    vector<int> dp(n + 1, 0);

    // dp[0][j] = 0 for all j.
    // dp[i][0] = 0 for all i.

    for (int i = 1; i <= m; ++i) {
      vector<int> curr = dp;
      for (int j = 1; j <= n; ++j) {
        // 1-indexed to 0-indexed
        if (s1[i - 1] == s2[j - 1]) {
          // dp[i-1][j-1] + 1
          curr[j] = dp[j - 1] + 1;
        } else {
          // Max of dp[i-1][j], dp[i][j-1]
          curr[j] = max(dp[j], curr[j - 1]);
        }
      }
      dp = std::move(curr);
    }
    return dp[n];
  }
};
