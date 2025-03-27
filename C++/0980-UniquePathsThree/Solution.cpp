#include <array>
#include <utility>
#include <vector>

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

constexpr int VISITED = -2;
constexpr int OBSTACLE = -1;
constexpr int EMPTY = 0;
constexpr int START = 1;
constexpr int END = 2;

class Solution {
 public:
  int uniquePathsIII(std::vector<std::vector<int>>& grid) {
    // compact into bitmasks?
    const int m = grid.size();
    const int n = grid[0].size();

    int srcR, srcC;
    int nodes = 1;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == START) {
          srcR = i;
          srcC = j;
        } else if (grid[i][j] == EMPTY) {
          ++nodes;
        }
      }
    }

    int result = 0;
    dfs(grid, srcR, srcC, nodes, result);
    return result;
  }

 private:
  void dfs(std::vector<std::vector<int>>& grid,
           int r,
           int c,
           int remaining,
           int& result) {
    if (grid[r][c] == END) {
      result += remaining == 0;
      return;
    }

    int original = std::exchange(grid[r][c], VISITED);
    --remaining;
    for (const auto [dr, dc] : directions) {
      int nr = r + dr;
      int nc = c + dc;

      if (nr < 0 || nc < 0 || nr >= grid.size() || nc >= grid[0].size() ||
          grid[nr][nc] < 0) {  // negative is either visited/obstacle.
        continue;
      }

      dfs(grid, nr, nc, remaining, result);
    }

    // backtrack.
    ++remaining;
    grid[r][c] = original;
  }
};
