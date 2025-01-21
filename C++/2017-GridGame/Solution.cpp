#include <algorithm>
#include <array>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 gridGame(std::vector<std::vector<int>>& grid) {
    // 2D grid of 2 x N,
    // grid[r][c] represent the number of points at (r, c).
    // Two robots, starting at (0, 0), Goal at (1, n-1).
    //
    // Only move right or down, collect points equivalent to sum of grid[r][c].
    // First Robot wants to minimize the Second Robot's points, and goes first.
    // Second Robot wants to maximise.
    // In a sense, both just wants to maximise.
    //
    // Naively, x2 BFS/Dijkstra would work with negated weights.
    // Can we do better?
    //
    // Notice that the Robots can NOT move back up after moving down.
    // There is also a single column where both rows are collected to move down.
    // Feels like DP.
    //
    // i.e., dp[r][c] represents maximum points at (r, c), with appropriate
    // state transitions. (i.e., space optimization is possible)
    // dp[0][c] = dp[0][c-1] + grid[0][c];
    // dp[1][c] = std::max(
    //                dp[0][c] + grid[1][c], // move down
    //                dp[1][c-1] + grid[1][c] // move right, at bottom row.
    //            )
    // Space Optimized:
    // Three States dp[0][c-1], dp[0][c] and dp[1][c-1].
    // Still need at least two scans though, and is non-trivial to mutate the
    // grid to reflect the zeroes.
    // Can we do better?
    //
    // Since the Robots cannot move back up, there exists a k, k in [1..N],
    // such that the first robot takes sum(0..k) of row 1, and sum(k+1..N) of
    // row 2, leaving sum(k+1..N) of row1 and sum(0..k) of row2.
    // Range Queries => Prefix Sums!
    const int n = grid[0].size();
    std::array<std::vector<i64>, 2> prefix{{
        std::vector<i64>(n + 1, 0LL),
        std::vector<i64>(n + 1, 0LL),
    }};
    for (int c = 1; c <= n; ++c) {
      prefix[0][c] = prefix[0][c - 1] + grid[0][c - 1];
      prefix[1][c] = prefix[1][c - 1] + grid[1][c - 1];
    }

    // Determine K, minimizing std::max(sum(row[1][k+1..N], sum(row[2][0..k]))
    i64 result = LLONG_MAX;
    for (int k = 0; k < n; ++k) {
      i64 top = prefix[0][n] - prefix[0][k + 1];
      i64 bottom = prefix[1][k] - prefix[1][0];

      result = std::min(result, std::max(top, bottom));
    }
    return result;
  }
};
