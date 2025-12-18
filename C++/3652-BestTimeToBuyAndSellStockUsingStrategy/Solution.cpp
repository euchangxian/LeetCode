#include <algorithm>
#include <vector>

using i64 = long long;

enum Strategy {
  Buy = -1,
  Hold = 0,
  Sell = 1,
};

class Solution {
 public:
  i64 maxProfit(std::vector<int>& prices, std::vector<int>& strategy, int k) {
    // prices[i]: price of a stock on the ith day.
    // strategy[i]: action on the ith day.
    //              -1 => buy one unit
    //               0 => hold
    //               1 => sell one unit
    // Given an EVEN integer k, perform at most one modficiation to strategy:
    // - select exactly k consecutive elements in strategy
    // - set the first k/2 elements to 0 (hold)
    // - set hte last k/2 elements to 1 (sell)
    // Profit is the sum of strategy[i] * prices[i] across all days.
    // Return the maximum profit.
    const auto n = static_cast<int>(prices.size());

    i64 baseProfit = 0;
    for (int i = 0; i < n; ++i) {
      baseProfit += strategy[i] * prices[i];
    }

    const auto half = k / 2;
    i64 delta = 0;

    // first window
    for (int i = 0; i < half; ++i) {
      delta += (Strategy::Hold * prices[i]) - (strategy[i] * prices[i]);
    }
    for (int i = half; i < k; ++i) {
      delta += (Strategy::Sell * prices[i]) - (strategy[i] * prices[i]);
    }

    i64 maxDelta = delta;
    for (int i = 1; i <= n - k; ++i) {
      // Hold -> Original Strategy
      i64 left =
          (Strategy::Hold * prices[i - 1]) - (strategy[i - 1] * prices[i - 1]);

      // Sell -> Hold
      // -1*prices[x] - (strategy[x]*prices[x])
      // 0*prices[x] - (strategy[x]*prices[x])
      i64 mid = Strategy::Sell * prices[i + half - 1];

      // Original Strategy -> Sell
      i64 right = (Strategy::Sell * prices[i + k - 1]) -
                  (strategy[i + k - 1] * prices[i + k - 1]);

      delta = delta - left - mid + right;

      maxDelta = std::max(maxDelta, delta);
    }
    return baseProfit + std::max(0LL, maxDelta);
  }
};
