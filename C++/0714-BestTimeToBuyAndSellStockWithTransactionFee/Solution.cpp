#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maxProfit(std::vector<int>& prices, int fee) {
    // can only buy one, sell one at any time. i.e., hold one stock only.
    // Transaction fee is charged for one Buy+Sell, not each buy, each sell.
    // At each day, there are 3 choices:
    // - buy,
    // - sell existing stock,
    // - hold existing cash/stock.
    // Very different from the problem that allows buying/holding fractional
    // stocks.
    // There are only two states: holding a stock, not holding a stock.
    // Therefore, determine the maximum profit.
    int notHolding = 0;
    int holding = -prices[0];
    for (int i = 1; i < prices.size(); ++i) {
      int held = holding;

      // notHolding -> holding, or holding -> holding
      holding = std::max(holding, notHolding - prices[i]);

      // holding -> notHolding, i.e., sell, or notHolding -> notHolding
      notHolding = std::max(notHolding, held + prices[i] - fee);
    }
    return notHolding;
  }
};
