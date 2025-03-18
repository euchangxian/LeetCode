#include <algorithm>
#include <vector>

class Solution {
 public:
  int minCostClimbingStairs(std::vector<int>& cost) {
    int n = cost.size();
    // dp[i] represents the min cost to reach the ith step
    std::vector<int> dp(n + 1, 0);

    for (int i = 2; i < n + 1; ++i) {
      dp[i] = std::min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }
    return dp[n];
  }
};
