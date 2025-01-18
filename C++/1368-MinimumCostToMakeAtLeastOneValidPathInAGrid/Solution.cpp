#include <array>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <utility>
#include <vector>

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},   // right
    {0, -1},  // left
    {1, 0},   // down
    {-1, 0},  // up
}};

class Solution {
 public:
  int minCost(std::vector<std::vector<int>>& grid) {
    // m x n grid.
    // grid[i][j] = 1 | 2 | 3 | 4 => Right | Left | Down | Up respectively.
    // Indicates moveable direction.
    //
    // Start at (0, 0). Goal at (m-1, n-1)
    // Pay cost of 1 to change grid direction.
    // Intuition: Dijkstra. Edge cost equals to 0 if direction is same as
    // grid[i][j], otherwise, 1.
    // Thus, can be further optimized to 0/1 BFS.
    const std::size_t m = grid.size();
    const std::size_t n = grid[0].size();

    std::deque<std::pair<int, int>> frontier;
    std::vector<std::vector<int>> distance(m, std::vector<int>(n, INT_MAX));

    frontier.emplace_front(0, 0);
    distance[0][0] = 0;
    while (!frontier.empty()) {
      auto [r, c] = frontier.front();
      frontier.pop_front();

      if (r == m - 1 && c == n - 1) {
        return distance[r][c];
      }

      for (int d = 1; d <= 4; ++d) {
        const auto [dr, dc] = directions[d - 1];

        int nr = r + dr;
        int nc = c + dc;
        if (nr < 0 || nc < 0 || nr >= m || nc >= n) {
          continue;
        }

        int newDist = distance[r][c] + (d != grid[r][c]);
        if (newDist >= distance[nr][nc]) {
          continue;
        }

        if (d == grid[r][c]) {
          frontier.emplace_front(nr, nc);
        } else {
          frontier.emplace_back(nr, nc);
        }
        distance[nr][nc] = newDist;
      }
    }

    // unreachable.
    return -1;
  }
};
