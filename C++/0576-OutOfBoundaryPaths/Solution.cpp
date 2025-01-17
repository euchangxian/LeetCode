#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

constexpr int MOD = 1'000'000'007;

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

using i64 = long long;
class Solution {
 public:
  int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
    // m x n grid with a ball, starting at [startRow, startColumn].
    // Move adjacent directions at most maxMove times.
    // Number of paths to move the ball out of the boundary.
    // Given constraints, complete search is possible.
    // But this does seem like DP.
    // Number of moves to move out at (r, c) with k moves.
    // Do a DFS exploring all paths.
    std::vector<std::vector<std::vector<int>>> memo(
        m, std::vector<std::vector<int>>(n, std::vector<int>(maxMove + 1, -1)));
    return dfs(m, n, memo, maxMove, startRow, startColumn);
  }

 private:
  int dfs(const int m,
          const int n,
          std::vector<std::vector<std::vector<int>>>& memo,
          int remainingMoves,
          int r,
          int c) {
    if (r < 0 || c < 0 || r >= m || c >= n) {
      return 1;
    }

    if (remainingMoves == 0) {
      return 0;
    }

    if (memo[r][c][remainingMoves] >= 0) {
      return memo[r][c][remainingMoves];
    }

    i64 sum = 0LL;
    for (const auto [dr, dc] : directions) {
      int nr = r + dr;
      int nc = c + dc;

      sum = (sum + dfs(m, n, memo, remainingMoves - 1, nr, nc)) % MOD;
    }

    memo[r][c][remainingMoves] = sum;
    return sum;
  }
};
