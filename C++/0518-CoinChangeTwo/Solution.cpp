#include <cstdint>
#include <vector>

class Solution {
 public:
  int change(int amount, std::vector<int>& coins) {
    // dp[amt] represents the number of ways to make up amt using the coins
    // dp[amt] = sum(dp[amt - coin])
    std::vector<uint32_t> dp(amount + 1, 0);
    dp[0] = 1;  // one way to make up an amount of 0

    for (const uint32_t& coin : coins) {
      for (std::size_t amt = coin; amt <= amount; ++amt) {
        dp[amt] += dp[amt - coin];
      }
    }
    return dp[amount];
  }
};
