#include <array>
#include <vector>

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

class Solution {
 public:
  bool containsCycle(std::vector<std::vector<char>>& grid) {
    // 2D grid of characters m x n.
    // Check if there is a cycle consisting of same values in grid.
    // i.e., DFS, but a cell is connected to another cell if and only if it has
    // the same values.
    const int m = grid.size();
    const int n = grid[0].size();

    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (visited[r][c]) {
          continue;
        }

        // returns true if there is a cycle.
        if (dfs(grid, visited, grid[r][c], -1, -1, r, c)) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  bool dfs(const std::vector<std::vector<char>>& grid,
           std::vector<std::vector<bool>>& visited,
           char match,
           int pR,
           int pC,
           int r,
           int c) {
    visited[r][c] = true;
    for (const auto [dr, dc] : directions) {
      int nr = r + dr;
      int nc = c + dc;

      if (nr < 0 || nc < 0 || nr >= grid.size() || nc >= grid[0].size() ||
          grid[nr][nc] != match) {
        continue;
      }

      // check not parent
      if (visited[nr][nc] && (pR != nr && pC != nc)) {
        return true;
      }

      if (!visited[nr][nc] && dfs(grid, visited, match, r, c, nr, nc)) {
        return true;
      }
    }

    return false;
  }
};
