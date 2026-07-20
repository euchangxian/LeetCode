#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> shiftGrid(std::vector<std::vector<int>>& grid,
                                          int k) {
    // Shift mxn grid k times. In one shift operation:
    // - grid[i][j] move to grid[i][j+1].
    // - grid[i][n-1] move to grid[i+1][0]
    // - grid[m-1][n-1] move to grid[0][0]
    //
    // Directionally:
    //  -->
    //   /
    //  /->
    // We can calculate the delta (row, col) for each cell.
    // deltaCol = k % n
    // deltaRow = (k / n)
    const auto m = static_cast<int>(grid.size());
    const auto n = static_cast<int>(grid[0].size());
    std::vector<std::vector<int>> result(m, std::vector<int>(n));

    for (auto r = 0; r < m; ++r) {
      for (auto c = 0; c < n; ++c) {
        auto shiftCol = (c + k) % n;
        auto deltaRow = (c + k) / n;
        auto shiftRow = (r + deltaRow) % m;
        result[shiftRow][shiftCol] = grid[r][c];
      }
    }
    return result;
  }
};
