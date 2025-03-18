#include <queue>
#include <vector>

class Solution {
 public:
  int orangesRotting(std::vector<std::vector<int>>& grid) {
    // BFS from each rotten orange. Count iterations
    int m = grid.size();
    int n = grid[0].size();

    int freshOranges = 0;
    std::queue<std::pair<int, int>> frontier;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          ++freshOranges;
        } else if (grid[i][j] == 2) {
          frontier.push({i, j});
        }
      }
    }

    if (freshOranges <= 0) {
      return 0;
    }

    // R, D, L, U
    const std::vector<std::pair<int, int>> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int time = 0;
    while (!frontier.empty() && freshOranges > 0) {
      ++time;
      int k = frontier.size();
      for (int i = 0; i < k && freshOranges > 0; ++i) {
        auto [r, c] = frontier.front();
        frontier.pop();

        for (const auto [dr, dc] : directions) {
          int nr = r + dr;
          int nc = c + dc;

          if (nr < 0 || nr >= m || nc < 0 || nc >= n || grid[nr][nc] == 0 ||
              grid[nr][nc] == 2) {
            continue;
          }

          grid[nr][nc] = 2;  // mark as rotten
          frontier.push({nr, nc});
          --freshOranges;
        }
      }
    }

    if (freshOranges > 0) {
      // Consider the case where the only rotten orange is not adjacent to any
      // fresh orange
      return -1;
    }

    return time;
  }
};
