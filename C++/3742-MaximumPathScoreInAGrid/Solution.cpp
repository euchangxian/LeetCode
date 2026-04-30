#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxPathScore(std::vector<std::vector<int>>& grid, int k) {
    // m*n Grid. Grid[i] = 0 | 1 | 2
    // Start from (0, 0), End at (m-1, n-1) by moving only right or down.
    // - 0: add 0 to score, costs 0
    // - 1: add 1, cost 1
    // - 2: add 2, cost 1
    // Return the maximum score achievable without exceeding a total cost of k.
    // -1 if no path exists.
    //
    // Seems like Knapsack DP at first glance.
    // - m, n <= 200
    // dp[i][j][cost] = max score at (i, j) with cost
    constexpr auto cost = [](auto x) { return std::min(x, 1); };

    const auto m = static_cast<int>(grid.size());
    const auto n = static_cast<int>(grid[0].size());

    auto dp = std::vector<std::vector<std::vector<int>>>(
        m, std::vector<std::vector<int>>(n, std::vector<int>(k + 1, -1)));

    dp[0][0][cost(grid[0][0])] = 0;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        auto cellCost = cost(grid[r][c]);

        for (int newCost = cellCost; newCost <= k; ++newCost) {
          auto& best = dp[r][c][newCost];
          if (r > 0) {
            best = std::max(best, dp[r - 1][c][newCost - cellCost]);
          }

          if (c > 0) {
            best = std::max(best, dp[r][c - 1][newCost - cellCost]);
          }

          if (best != -1) {
            best += grid[r][c];
          }
        }
      }
    }
    return *std::ranges::max_element(dp[m - 1][n - 1]);
  }
};
