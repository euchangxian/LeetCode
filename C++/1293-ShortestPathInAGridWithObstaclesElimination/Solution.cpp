#include <array>
#include <cstddef>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;
class Solution {
 private:
  // Need to consider all 4 directions instead of just right and bottom. This
  // is to deal with the situation where the obstacle blocks right/bottom, and
  // the only path is left/top
  static constexpr std::array<std::pair<int, int>, 4> directions{
      {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

 public:
  int shortestPath(vector<vector<int>>& grid, int k) {
    // grid[i][j] = 0 (empty) | 1 (obstacle)
    // Move in cardinal directions to an empty cell.
    // k is the number of obstacles that can be eliminated.
    //
    // Start (0, 0), Goal (m-1, n-1)
    // Intuition is just BFS with an extra state to represent the number of
    // obstacles break remaining.
    const size_t rows = grid.size();
    const size_t cols = grid[0].size();
    if (k >= rows + cols - 2) {
      // manhattan dist between (0, 0) and (rows-1, cols-1)
      // This optimization is necessary to avoid unnecessary traversal if we
      // can determine that we can just break through all obstacles.
      return rows + cols - 2;
    }

    std::queue<std::tuple<int, int, int>> frontier;
    std::vector<std::vector<std::vector<bool>>> seen(
        rows,
        std::vector<std::vector<bool>>(cols, std::vector<bool>(k + 1, false)));
    frontier.emplace(0, 0, k);
    seen[0][0][k] = true;

    int steps = 0;
    while (!frontier.empty()) {
      int size = frontier.size();
      while (size--) {
        const auto [r, c, breaks] = frontier.front();
        frontier.pop();

        if (r == rows - 1 && c == cols - 1) {
          return steps;
        }

        for (const auto& [dr, dc] : directions) {
          const int nr = r + dr;
          const int nc = c + dc;

          if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) {
            continue;
          }

          int newBreaks = breaks - grid[nr][nc];
          if ((grid[nr][nc] == 1 && breaks <= 0) || seen[nr][nc][newBreaks]) {
            // note we check newBreaks AFTER checkin of breaks <= 0.
            // Avoid negative indexing.
            continue;
          }

          frontier.emplace(nr, nc, newBreaks);
          seen[nr][nc][newBreaks] = true;
        }
      }
      ++steps;
    }
    return -1;
  }
};
