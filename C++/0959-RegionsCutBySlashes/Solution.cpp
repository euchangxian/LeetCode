#include <string>
#include <vector>

class Solution {
 public:
  int regionsBySlashes(std::vector<std::string>& grid) {
    int n = grid.size();

    // 0 represents not blocked.
    std::vector<std::vector<bool>> expandedGrid(3 * n,
                                                std::vector<bool>(3 * n, 0));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        // Map each original 1x1 cell to a 3x3 cell. This is to handle the case
        // where 'cells' are diagonally accessible in a 1x1 or 2x2, but DFS can
        // only go to adjacent cells.
        // Map the original coordinates to the expanded coordinates
        int r = i * 3;
        int c = j * 3;
        if (grid[i][j] == ' ') {
          continue;
        } else if (grid[i][j] == '\\') {
          expandedGrid[r][c] = 1;
          expandedGrid[r + 1][c + 1] = 1;
          expandedGrid[r + 2][c + 2] = 1;
        } else if (grid[i][j] == '/') {
          expandedGrid[r][c + 2] = 1;
          expandedGrid[r + 1][c + 1] = 1;
          expandedGrid[r + 2][c] = 1;
        }
      }
    }

    // Perform DFS to find disjoint islands
    std::vector<std::vector<bool>> seen(3 * n, std::vector<bool>(3 * n, 0));
    int regions = 0;
    for (int r = 0; r < 3 * n; ++r) {
      for (int c = 0; c < 3 * n; ++c) {
        if (!expandedGrid[r][c] && !seen[r][c]) {
          dfs(expandedGrid, seen, r, c);
          ++regions;
        }
      }
    }
    return regions;
  }

 private:
  void dfs(const std::vector<std::vector<bool>>& blocked,
           std::vector<std::vector<bool>>& seen,
           int r,
           int c) {
    if (r < 0 || c < 0 || r >= blocked.size() || c >= blocked[0].size() ||
        blocked[r][c] || seen[r][c]) {
      return;
    }

    seen[r][c] = 1;

    // right, down, left, up
    std::vector<std::pair<int, int>> neighbours = {
        {r, c + 1}, {r + 1, c}, {r, c - 1}, {r - 1, c}};
    for (const auto& [nr, nc] : neighbours) {
      dfs(blocked, seen, nr, nc);
    }
    return;
  }
};
