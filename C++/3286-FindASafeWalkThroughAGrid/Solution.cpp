#include <array>
#include <cstddef>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;
class Solution {
 private:
  static constexpr std::array<std::pair<int, int>, 4> directions{
      {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

 public:
  bool findSafeWalk(vector<vector<int>>& grid, int health) {
    // Straightforward BFS. No need to count steps. Just return true/false
    // if can reach.
    const size_t rows = grid.size();
    const size_t cols = grid[0].size();

    // small optimization to check if health is greater than the manhattan dist.
    if (health - grid[0][0] > static_cast<int>((rows - 1) + (cols - 1))) {
      return true;
    }

    // Stores the highest hp seen at the cell (r, c).
    // In BFS, the shortest path to the cell is explored. If the HP seen at
    // (nr, nc) is higher than the current HP, then we can prune the tree.
    // No path through (nr, nc) with a lower HP can yield a better outcome.
    std::vector<std::vector<int>> seen(rows, std::vector<int>(cols, 0));

    // {row, col, health}
    std::queue<std::tuple<int, int, int>> frontier;
    frontier.emplace(0, 0, health - grid[0][0]);
    seen[0][0] = health - grid[0][0];

    while (!frontier.empty()) {
      int size = frontier.size();
      while (size--) {
        const auto [r, c, hp] = frontier.front();
        frontier.pop();

        if (r == rows - 1 && c == cols - 1) {
          return true;
        }

        for (const auto [dr, dc] : directions) {
          const int nr = r + dr;
          const int nc = c + dc;

          if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) {
            continue;
          }

          const int remainingHp = hp - grid[nr][nc];
          if (remainingHp <= 0 || remainingHp <= seen[nr][nc]) {
            continue;
          }

          frontier.emplace(nr, nc, remainingHp);
          seen[nr][nc] = remainingHp;
        }
      }
    }
    return false;
  }
};
