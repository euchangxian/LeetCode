#include <array>
#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

class Solution {
 public:
  int getFood(std::vector<std::vector<char>>& grid) {
    // Seems to be just a straightforward BFS.
    const std::size_t rows = grid.size();
    const std::size_t cols = grid[0].size();

    auto [startR, startC] = [rows, cols, &grid]() -> std::pair<int, int> {
      // Find the starting coordinates.
      for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
          if (grid[r][c] == '*') {
            return {r, c};
          }
        }
      }
      // unreachable
      return {-1, -1};
    }();

    constexpr std::array<std::pair<int, int>, 4> directions{{
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0},
    }};

    // BFS with {startX, startC} from the start.
    std::queue<std::pair<int, int>> frontier;
    frontier.emplace(startR, startC);
    grid[startR][startC] = 'X';

    int distance = 0;
    while (!frontier.empty()) {
      size_t frontierSize = frontier.size();
      while (frontierSize--) {
        const auto [currR, currC] = frontier.front();
        frontier.pop();

        // Do goal-checks before adding to the frontier.
        for (const auto [dr, dc] : directions) {
          const int nr = currR + dr;
          const int nc = currC + dc;

          if (nr < 0 || nc < 0 || nr >= rows || nc >= cols ||
              grid[nr][nc] == 'X') {
            continue;
          }

          if (grid[nr][nc] == '#') {
            return distance + 1;
          }

          frontier.emplace(nr, nc);

          // mark as visited by denoting it as a wall.
          grid[nr][nc] = 'X';
        }
      }
      ++distance;
    }

    return -1;
  }
};
