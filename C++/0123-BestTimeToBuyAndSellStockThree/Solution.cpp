#include <algorithm>
#include <array>
#include <vector>

class Solution {
 public:
  int maxProfit(std::vector<int>& prices) {
    // converting top-down to bottom-up is less straightforward.
    // Notice that we only need dp[i+1] to compute dp[i].
    // Thus, we can convert to constant space.
    const int n = prices.size();

    // Extra k+1 to simplify bound-checking.
    std::vector<std::array<int, 5>> dp(n + 1, std::array<int, 5>{});
    for (int i = n - 1; i >= 0; --i) {
      for (int k = 0; k < 4; ++k) {
        dp[i][k] = dp[i + 1][k];  // skip

        int delta = (k % 2 == 0) ? -prices[i] : prices[i];
        dp[i][k] = std::max(dp[i][k], dp[i + 1][k + 1] + delta);
      }
    }
    return dp[0][0];
  }

  int maxProfitTopDown(std::vector<int>& prices) {
    // prices[i] is the price on the ith day.
    // Maximum profit with at most 2 transactions.
    // Each buy-sell is considered 1 transaction.
    // Enumerate all possibilities, 0, 1, 2 transactions I guess.
    // Then, it becomes somewhat like Buy and Sell Stock One.
    //
    // Observe that we can only hold one stock at most. Thus, the most naive
    // approach would be to find an index i such that we can partition
    // nums[0..i] and nums[i+1..n-1], then take the sum of BuyAndSellStockOne on
    // the partitions. O(N^2).
    //
    // How can we do better?
    // Is there any pattern observed from the partitioning that provides the
    // maximum profit?
    // Not entirely sure how to handle the "at most 2 transactions".
    //
    // Consider naive recursion.
    // We minimally need state(i, k), f(i, k) returns the maximum profit from
    // performing k transactions on prices[..i].
    // Note that we need a way to know if we are not holding a stock, so we can
    // buy on day i, or holding a stock to sell on day i.
    // Since we can only hold at most one stock, we can use even-odd k, starting
    // from 0: buy, 1: sell
    //
    // Thus, the transitions can be modelled as:
    // f(i, k) = max{
    //   f(i+1, k),
    //   f(i+1, k+1) - prices[i] if k is even
    //   f(i+1, k+1) + prices[i] if k is odd
    // }
    const int n = prices.size();
    std::vector<std::vector<int>> memo(n, std::vector<int>(4, -1));

    return dfs(prices, memo, 0, 0);
  }

 private:
  int dfs(const std::vector<int>& prices,
          std::vector<std::vector<int>>& memo,
          int i,
          int k) {
    if (i >= prices.size()) {
      return 0;
    }

    if (k == 4) {
      return 0;  // no more further transactions
    }

    int& ans = memo[i][k];
    if (ans != -1) {
      return ans;
    }

    ans = dfs(prices, memo, i + 1, k);

    // if even, buy, else sell
    int delta = (k % 2 == 0) ? -prices[i] : prices[i];
    ans = std::max(ans, dfs(prices, memo, i + 1, k + 1) + delta);
    return ans;
  }
};
