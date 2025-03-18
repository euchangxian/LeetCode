#include <algorithm>
#include <vector>

class Solution {
 private:
  int const INF = 10e4 + 1;

 public:
  int coinChange(std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, INF);
    dp[0] = 0;
    for (int const& coin : coins) {
      if (coin > amount) {
        continue;
      }
      dp[coin] = 1;
    }

    for (int i = 1; i <= amount; ++i) {
      for (int const& coin : coins) {
        if (i - coin >= 0) {
          dp[i] = std::min(dp[i], 1 + dp[i - coin]);
        }
      }
    }

    return dp[amount] != INF ? dp[amount] : -1;
  }
};
