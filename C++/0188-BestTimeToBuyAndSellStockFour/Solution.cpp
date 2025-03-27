#include <algorithm>
#include <array>
#include <utility>
#include <vector>

constexpr int MAX_N = 1000;
constexpr int MAX_K = 100;

class Solution {
 public:
  int maxProfit(int k, std::vector<int>& prices) {
    const int n = prices.size();
    std::array<int, 2 * MAX_K + 1> prev{}, dp{};
    for (int i = n - 1; i >= 0; --i) {
      for (int j = 0; j < 2 * k; ++j) {
        int delta = (j % 2 == 0) ? -prices[i] : prices[i];
        dp[j] = std::max(prev[j], prev[j + 1] + delta);
      }
      prev = std::move(dp);
    }
    return dp[0];
  }

  int maxProfit2D(int k, std::vector<int>& prices) {
    const int n = prices.size();

    // Note the transition: dp[i][j] = max(dp[i+1][j], dp[i+1][j+1])
    // This means we need to iterate in reverse.
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2 * k + 1, 0));

    for (int i = n - 1; i >= 0; --i) {
      for (int j = 0; j < 2 * k; ++j) {
        int delta = (j % 2 == 0) ? -prices[i] : prices[i];
        dp[i][j] = std::max(dp[i + 1][j], dp[i + 1][j + 1] + delta);
      }
    }
    return dp[0][0];
  }

  int maxProfitTopDown(int k, std::vector<int>& prices) {
    // Similar to 123. Buy and Sell Stock Three, except instead of 2
    // transactions, we have k transactions limit.
    // Similarly, we can use even numbers to denote Buy, odd to denote Sells.
    const int n = prices.size();
    std::vector<std::vector<int>> memo(n, std::vector<int>(2 * k, -1));
    return dfs(k, prices, memo, 0, 0);
  }

 private:
  int dfs(const int k,
          const std::vector<int>& prices,
          std::vector<std::vector<int>>& memo,
          int i,
          int j) {
    if (i >= prices.size()) {
      return 0;
    }

    if (j >= 2 * k) {
      return 0;
    }

    int& ans = memo[i][j];
    if (ans != -1) {
      return ans;
    }

    ans = dfs(k, prices, memo, i + 1, j);

    // if even, buy, else sell
    int delta = (j % 2 == 0) ? -prices[i] : prices[i];
    ans = std::max(ans, dfs(k, prices, memo, i + 1, j + 1) + delta);
    return ans;
  }
};
