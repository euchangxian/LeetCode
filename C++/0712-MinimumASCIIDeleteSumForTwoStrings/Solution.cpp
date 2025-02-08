#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  int minimumDeleteSum(std::string_view s1, std::string_view s2) {
    // Seems like Longest Common Subsequence, but keep track of the actual
    // characters in the sequence.
    // Actually, closer to Edit Distance.
    const int m = s1.size();
    const int n = s2.size();

    // After the ith iteration, dp[j] represents the minimum delete sum to
    // make s1[:i] == s2[:j].
    std::vector<int> dp(n + 1);
    dp[0] = 0;
    for (int j = 1; j <= n; ++j) {
      // Base Case, delete characters from s2.
      dp[j] = dp[j - 1] + s2[j - 1];
    }

    std::vector<int> curr(n + 1);
    for (int i = 1; i <= m; ++i) {
      curr[0] = dp[0] + s1[i - 1];  // s1[:i] delete sum to make 0-length.

      for (int j = 1; j <= n; ++j) {
        if (s1[i - 1] == s2[j - 1]) {
          curr[j] = dp[j - 1];
          continue;
        }

        // delete from s1, dp[i-1][j] + s1[i-1]
        // delete from s2, dp[i][j-1] + s2[j-1]
        curr[j] = std::min(dp[j] + s1[i - 1], curr[j - 1] + s2[j - 1]);
      }
      std::swap(dp, curr);
    }
    return dp[n];
  }
};
