#include <vector>

class Solution {
 public:
  int maxProfit(std::vector<int>& prices) {
    // Two Choices: Buy or Sell (if already bought a stock)
    // For this variant, only one single stock can be bought and sold.
    // Sliding window / monotonically non-decreasing stack.
    if (prices.size() < 2) {
      return 0;
    }

    int profit = 0;
    int l = 0;
    for (int r = 1; r < prices.size(); ++r) {
      if (prices[r] < prices[l]) {
        l = r;  // try buying at r
        continue;
      }
      profit = std::max(profit, prices[r] - prices[l]);
    }

    return profit;
  }
};
