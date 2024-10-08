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
  int uniquePaths(int m, int n) {
    // After the ith iteration, dp[j] represents the number of unique paths that
    // the robot can take to reach grid[i][j]
    // Base case: one path going right-wards
    vector<int> dp(n, 1);
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[j] = dp[j - 1] + dp[j];
      }
    }
    return dp[n - 1];
  }
};
