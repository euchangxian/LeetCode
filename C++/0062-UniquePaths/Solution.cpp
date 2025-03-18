#include <vector>

class Solution {
 public:
  int uniquePaths(int m, int n) {
    // After the ith iteration, dp[j] represents the number of unique paths that
    // the robot can take to reach grid[i][j]
    // Base case: one path going right-wards
    std::vector<int> dp(n, 1);
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[j] = dp[j - 1] + dp[j];
      }
    }
    return dp[n - 1];
  }
};
