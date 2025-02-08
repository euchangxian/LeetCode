#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <numeric>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  int minDistance(std::string_view word1, std::string_view word2) {
    const int m = word1.size();
    const int n = word2.size();

    // After the i-th iteration, dp[j] represents the minimum number of
    // insert|delete|replace operations required to convert word1[:i] to
    // word2[:j].
    std::vector<int> dp(n + 1);

    // Set up base case, j add operations.
    std::iota(dp.begin(), dp.end(), 0);

    std::vector<int> curr(n + 1);
    for (int i = 1; i <= m; ++i) {
      curr[0] = i;  // i delete operations.
      for (int j = 1; j <= n; ++j) {
        if (word1[i - 1] == word2[j - 1]) {
          // same cost as previous state
          curr[j] = dp[j - 1];
          continue;
        }

        // an operation is necessary.
        // insert:  dp[i][j-1], insert word2[j-1] to match word2[:j]
        // delete:  dp[i-1][j], delete word1[i-1].
        // replace: dp[i-1][j-1], replace word1[i-1] with word2[j-1].
        curr[j] = 1 + std::min({
                          curr[j - 1],
                          dp[j],
                          dp[j - 1],
                      });
      }
      std::swap(dp, curr);
    }
    return dp[n];
  }
};
