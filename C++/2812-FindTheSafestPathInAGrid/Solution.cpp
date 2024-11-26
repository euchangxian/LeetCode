#include <algorithm>
#include <array>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <queue>
#include <vector>

class Solution {
 private:
  std::array<std::array<int, 2>, 4> directions{{
      {0, 1},
      {1, 0},
      {0, -1},
      {-1, 0},
  }};

 public:
  int maximumSafenessFactor(std::vector<std::vector<int>>& grid) {
    // Cell with a Thief '1', or empty '0'.
    // The safety value of a cell is the Manhattan Distance to the closest
    // thief.
    // The safety value of a path from (0, 0) to (n-1, n-1) is the minimum
    // safety value of the cells in the path.
    // Want: Maximum safety path.
    //
    // Probably precompute the safety value of each cell using multi-source BFS.
    // Then, Dijkstra? Greedily pick the highest safety value neighbour.
    const size_t n = grid.size();

    // small optimization to return early if a thief is on the source/dest
    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
      return 0;
    }

    // find all thiefs positions
    std::queue<std::array<int, 2>> frontier;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          frontier.push({i, j});
          grid[i][j] = 0;  // simultaneously update safety value.
        } else {
          grid[i][j] = -1;  // to be computed.
        }
      }
    }

    // BFS
    while (!frontier.empty()) {
      int sz = frontier.size();
      while (sz--) {
        auto [r, c] = frontier.front();
        frontier.pop();

        for (auto [dr, dc] : directions) {
          int nr = r + dr;
          int nc = c + dc;

          if (nr < 0 || nc < 0 || nr >= n || nc >= n || grid[nr][nc] != -1) {
            // if out of bounds or already "visited"
            continue;
          }

          grid[nr][nc] = grid[r][c] + 1;
          frontier.push({nr, nc});
        }
      }
    }

    // dijkstra or BFS should work fine. Need to maintain path safety value
    // as state.
    // {safety, r, c}
    std::priority_queue<std::array<int, 3>> maxHeap;
    maxHeap.push({grid[0][0], 0, 0});
    grid[0][0] = INT_MAX;  // mark as visited.
    while (!maxHeap.empty()) {
      auto [safety, r, c] = maxHeap.top();
      maxHeap.pop();

      if (r == n - 1 && c == n - 1) {
        return safety;
      }

      for (const auto& [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr >= n || nc >= n || grid[nr][nc] == -1) {
          continue;
        }
        maxHeap.push({std::min(safety, grid[nr][nc]), nr, nc});
        grid[nr][nc] = -1;
      }
    }

    return -1;  // should not reach here.
  }
};
