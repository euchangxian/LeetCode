#include <algorithm>
#include <climits>
#include <vector>

class Solution {
 public:
  int maxProfit(std::vector<int>& prices) {
    // Decision tree looks like:
    // 1. Buy. IF currently not holding any stock. Therefore a state is
    //    necessary
    // 2. Sell. IF holding a stock. Cooldown of 1 day must be applied.
    // 3. Do nothing. Rest. equivalent to a cooldown
    //
    // Resembles a State Machine.
    //
    // Buy -> Sell or Buy -> Rest
    // Sell -> Rest
    // Rest -> Buy or Rest -> Sell
    const std::size_t n{prices.size()};

    // Initialize base cases. Buy on first day, Sell is not possible. Rest is 0
    int buy{-prices[0]};
    int sell{INT_MIN};
    int rest{0};

    // For each day
    for (std::size_t i{1}; i < n; ++i) {
      const int prevSell{sell};

      // Buy -> Sell. Note the order is important as cannot buy and sell on the
      // same day
      sell = buy + prices[i];

      // Buy -> Hold, keeping the previous bought stock, or Rest -> Buy
      buy = std::max(buy, rest - prices[i]);

      // Rest -> Rest or Sell -> Rest
      rest = std::max(rest, prevSell);
    }
    return std::max(sell, rest);
  }
};
