#include <algorithm>
#include <array>
#include <vector>

using i64 = long long;

constexpr auto MAX_N = 1000;

enum Inv {
  None,
  Long,
  Short,
};

class Solution {
 public:
  i64 maximumProfit(std::vector<int>& prices, int k) {
    //  prices[i] is the price of a stock on the ith day.
    //  Make at most k transactions.
    //  - Normal transaction: buy on day i, sell on day j where i < j.
    //    Profit = prices[j] - prices[i]
    //  - Short selling: Sell on day i, buy on day j.
    //    Profit = prices[i] - prices[j]
    // Each transaction must be completed before starting another.
    // Cannot start a transaction on the same day a previous transaction was
    // closed.
    // Return the maximum profit from making at most k transactions.
    //
    // Local Peaks and Valleys?
    // Except we can't buy/sell after selling/buying on the same day.
    // So there is an element of choice here.
    // e.g.,: prices = [8, 9, 1]
    // 8 is a local minima: buy
    // 9 is a local maxima: sell
    // profit = 1.
    // If we buy on prices[1]=9, sell on prices[2]=1, profit=8 instead.
    // There's also k.
    //
    // Model the inventory of the stock? -1, 0, 1.
    // That way, we can constrain transitions.
    // Seems like a 3-state DP, dp[i][k][inventory]?

    // state = 0|1|2
    // 0 => Not Holding
    // 1 => Long
    // 2 => Short
    const auto n = static_cast<int>(prices.size());
    std::array<std::array<i64, 3>, MAX_N / 2 + 1> dp{};

    dp[0][Inv::None] = 0;
    for (int j = 1; j <= k; ++j) {
      dp[j][Inv::Long] = -prices[0];
      dp[j][Inv::Short] = prices[0];
    }

    for (int i = 1; i < n; ++i) {
      // space-optimisation to 2-state DP by iterating in reverse.
      for (int j = k; j > 0; --j) {
        dp[j][Inv::None] =
            std::max({dp[j][Inv::None], dp[j][Inv::Long] + prices[i],
                      dp[j][Inv::Short] - prices[i]});

        dp[j][Inv::Long] =
            std::max(dp[j][Inv::Long], dp[j - 1][Inv::None] - prices[i]);
        dp[j][Inv::Short] =
            std::max(dp[j][Inv::Short], dp[j - 1][Inv::None] + prices[i]);
      }
    }
    return dp[k][Inv::None];
  }
};
