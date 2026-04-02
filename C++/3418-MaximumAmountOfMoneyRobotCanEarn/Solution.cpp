#include <algorithm>
#include <array>
#include <vector>

class Solution {
 public:
  int maximumAmount(std::vector<std::vector<int>>& coins) {
    // m*n grid. Start at (0, 0), reach (m-1,n-1).
    // Can move either right or down.
    // - Add coins[i][j] at every step.
    // - At most 2 negative coins[i][j] can be converted to 0.
    // Return the maximum coins.
    //
    // 3D shortest-path.
    // BFS is sufficient.
    // DP-like, actually.
    // dp[i][j][k], k=[0..2], representing the maximum coins obtainable at
    // (i,j), after using the power k times..
    const auto m = static_cast<int>(coins.size());
    const auto n = static_cast<int>(coins[0].size());

    constexpr auto INF = 1000 * 500 * 500;
    auto dp = std::vector<std::vector<std::array<int, 3>>>(
        m, std::vector<std::array<int, 3>>(n, {-INF, -INF, -INF}));
    dp[0][0][0] = coins[0][0];
    dp[0][0][1] = dp[0][0][2] = std::max(coins[0][0], 0);
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (r == 0 && c == 0) {
          continue;
        }
        std::array<int, 3> prev{-INF, -INF, -INF};
        if (r > 0) {
          prev = dp[r - 1][c];
        }

        if (c > 0) {
          prev[0] = std::max(prev[0], dp[r][c - 1][0]);
          prev[1] = std::max(prev[1], dp[r][c - 1][1]);
          prev[2] = std::max(prev[2], dp[r][c - 1][2]);
        }

        // no power
        dp[r][c][0] = prev[0] + coins[r][c];

        // max(no power, use power)
        dp[r][c][1] =
            std::max(prev[0] + std::max(0, coins[r][c]), prev[1] + coins[r][c]);
        dp[r][c][2] =
            std::max(prev[1] + std::max(0, coins[r][c]), prev[2] + coins[r][c]);
      }
    }

    return std::ranges::max(dp[m - 1][n - 1]);
  }
};
