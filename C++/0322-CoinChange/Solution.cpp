#include <algorithm>
#include <array>
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
 private:
  int const INF = 10e4 + 1;

 public:
  int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INF);
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
          dp[i] = min(dp[i], 1 + dp[i - coin]);
        }
      }
    }

    return dp[amount] != INF ? dp[amount] : -1;
  }
};
