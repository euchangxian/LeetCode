#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstdint>
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
  int change(int amount, vector<int>& coins) {
    // dp[amt] represents the number of ways to make up amt using the coins
    // dp[amt] = sum(dp[amt - coin])
    vector<uint32_t> dp(amount + 1, 0);
    dp[0] = 1;  // one way to make up an amount of 0

    for (const uint32_t& coin : coins) {
      for (size_t amt = coin; amt <= amount; ++amt) {
        dp[amt] += dp[amt - coin];
      }
    }
    return dp[amount];
  }
};
