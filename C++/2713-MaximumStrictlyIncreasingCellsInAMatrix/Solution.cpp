#include <algorithm>
#include <map>
#include <utility>
#include <vector>

class Solution {
 public:
  int maxIncreasingCells(std::vector<std::vector<int>>& grid) {
    // 1-indexed m*n integer matrix.
    // Select any cell as start.
    // - From the starting cell, can move to cardinal cells
    //   IF grid[r][c] < grid[nr][nc].
    // Find the longest path.
    // Topological Sort. DFS. DP
    // WARNING: NOT cardinal cells. To ANY cells in the same row/column.
    // This complicates the Graph creation.
    // Clearly, naively enumerating will not work, given m,n <= 10^5
    // Will need to maintain row/column longestPath.
    // Then, iterate in sorted order.
    const int m = grid.size();
    const int n = grid[0].size();
    std::map<int, std::vector<std::pair<int, int>>> values;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        values[grid[r][c]].emplace_back(r, c);
      }
    }

    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
    std::vector<int> rowLP(m, 0);
    std::vector<int> colLP(n, 0);
    int result = 1;

    // NOTE:
    // - Given that values is an Ordered Map of values, the order of iteration
    //   guarantees that we can always extend an existing Longest Path.
    // - Three separate DS is required.
    //   dp[r][c] represents the longest path ending at (r, c).
    //   rowLP[r] represents the longest path ending at row r.
    //   colLP[c] represents the longest path ending at column c.
    // - Thus, at each step, we update the longest path ending at (r, c).
    //   This can be derived from the longest path ending at rows r or column c,
    //   since cells are connected if they are in the same row/column (and
    //   strictly increasing value).
    //   Then, update the rowLP, colLP for the next step.
    for (const auto& [val, cells] : values) {
      for (const auto [r, c] : cells) {
        // Update LPs ending at this cell first.
        dp[r][c] = std::max(rowLP[r], colLP[c]) + 1;
        result = std::max(result, dp[r][c]);
      }

      for (const auto [r, c] : cells) {
        rowLP[r] = std::max(rowLP[r], dp[r][c]);
        colLP[c] = std::max(colLP[c], dp[r][c]);
      }
    }
    return result;
  }
};
