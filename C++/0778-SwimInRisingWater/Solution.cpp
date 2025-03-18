#include <algorithm>
#include <array>
#include <functional>
#include <queue>
#include <vector>

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

class Solution {
 public:
  int swimInWater(std::vector<std::vector<int>>& grid) {
    // grid[i][j] represents the elevation at (i, j)
    // At time t, the depth of the water everywhere is t.
    // We can move to a neighboring cell if its elevation is at most t.

    // The intuition is to traverse cells from lower to higher elevations,
    // keeping track of the maximum elevation encountered.
    // The time needed is the maximum elevation in the path to the destination.
    int n = grid.size();

    // Stores {elevation, row, col}
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>,
                        std::greater<std::tuple<int, int, int>>>
        minHeap;

    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
    visited[0][0] = true;
    minHeap.emplace(grid[0][0], 0, 0);

    int time = 0;
    while (!minHeap.empty()) {
      auto [elevation, r, c] = minHeap.top();
      minHeap.pop();
      time = std::max(time, elevation);

      if (r == n - 1 && c == n - 1) {
        break;
      }

      for (const auto& [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr >= n || nc >= n || visited[nr][nc]) {
          continue;
        }
        visited[nr][nc] = true;
        minHeap.emplace(grid[nr][nc], nr, nc);
      }
    }

    return time;
  }
};
