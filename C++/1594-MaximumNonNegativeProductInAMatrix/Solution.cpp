#include <algorithm>
#include <array>
#include <vector>

constexpr std::size_t MAX_MN = 15;
constexpr int MOD = 1E9 + 7;
class Solution {
 public:
  int maxProductPath(std::vector<std::vector<int>>& grid) {
    // m*n grid.
    // Start at (0, 0), move right or down only.
    // Find the path ending at (m-1, n-1) with the maximum non-negative product,
    // module 1E9+7, or -1 if the max product is negative.
    //
    // - We cannot eliminate paths preliminarily.
    // - Magnitude is not the only consideration.
    // - We can only go right-down
    // Mhm. Constraints are small enough to search the entire space?
    const auto m = static_cast<int>(grid.size());
    const auto n = static_cast<int>(grid[0].size());

    // 0: positive, 1: negative
    // Keep track of maximum positive, minimum negative.
    // i.e., largest magnitude.
    std::array<std::array<long long, MAX_MN + 1>, 2> dp{};
    dp[0][0] = dp[1][0] = grid[0][0];
    for (int c = 1; c < n; ++c) {
      dp[0][c] = dp[1][c] = grid[0][c] * dp[0][c - 1];
    }

    for (int r = 1; r < m; ++r) {
      dp[0][0] = dp[1][0] = dp[0][0] * grid[r][0];
      for (int c = 1; c < n; ++c) {
        if (grid[r][c] >= 0) {
          dp[0][c] = std::max(dp[0][c], dp[0][c - 1]);
          dp[1][c] = std::min(dp[1][c], dp[1][c - 1]);
        } else {
          // unreadable, just for fun.
          dp[1][c] = std::max(
              std::exchange(dp[0][c], std::min(dp[1][c], dp[1][c - 1])),
              dp[0][c - 1]);
        }

        dp[0][c] *= grid[r][c];
        dp[1][c] *= grid[r][c];
      }
    }

    return dp[0][n - 1] >= 0 ? dp[0][n - 1] % MOD : -1;
  }
};
