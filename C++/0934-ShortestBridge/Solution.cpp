#include <array>
#include <queue>
#include <utility>
#include <vector>

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

class Solution {
 public:
  int shortestBridge(std::vector<std::vector<int>>& grid) {
    // nxn binary matrix, 1 represents Land, 0 represents Water.
    // An island is a cardinally connected group of 1s.
    // There are exactly 2 islands.
    // Find the minimum number of 0s that to 1s to form one island.
    //
    // Seems like DFS to find '1's.
    // BFS from boundaries of the first island to find the first '1' that is
    // not part of itself?
    // We can determine boundaries - 0s beside 1s.
    // Multi-source BFS.
    const auto n = static_cast<int>(grid.size());

    auto valid = [&](int r, int c) {
      return r >= 0 && c >= 0 && r < n && c < n;
    };

    std::queue<std::pair<int, int>> frontier;
    auto dfs = [&](this auto&& dfs, int r, int c) -> void {
      for (auto [dr, dc] : directions) {
        auto nr = r + dr;
        auto nc = c + dc;

        if (!valid(nr, nc) || grid[nr][nc] == 2) {
          continue;
        }

        auto cell = std::exchange(grid[nr][nc], 2);  // visited
        if (cell == 0) {
          frontier.emplace(nr, nc);
        } else {
          dfs(nr, nc);
        }
      }
    };

    bool found = false;
    for (auto r = 0; r < n; ++r) {
      for (auto c = 0; c < n; ++c) {
        if (grid[r][c] == 1) {
          grid[r][c] = 2;
          found = true;
          dfs(r, c);
          break;
        }
      }

      if (found) {
        break;
      }
    }

    // BFS
    int steps = 1;
    while (!frontier.empty()) {
      auto sz = static_cast<int>(frontier.size());
      while (sz--) {
        auto [r, c] = frontier.front();
        frontier.pop();

        for (auto [dr, dc] : directions) {
          auto nr = r + dr;
          auto nc = c + dc;

          if (!valid(nr, nc) || grid[nr][nc] == 2) {
            continue;
          }

          auto cell = std::exchange(grid[nr][nc], 2);
          if (cell == 1) {
            return steps;
          }
          frontier.emplace(nr, nc);
        }
      }
      ++steps;
    }

    // input should have a valid answer.
    std::unreachable();
  }
};
