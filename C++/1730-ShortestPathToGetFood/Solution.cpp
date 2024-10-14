#include <array>
#include <cstddef>
#include <queue>
#include <vector>

using namespace std;
class Solution {
 public:
  int getFood(vector<vector<char>>& grid) {
    // Seems to be just a straightforward BFS.
    const size_t rows = grid.size();
    const size_t cols = grid[0].size();

    int startR;
    int startC;

    // Find the starting coordinates.
    for (size_t r = 0; r < rows; ++r) {
      for (size_t c = 0; c < cols; ++c) {
        if (grid[r][c] == '*') {
          startR = r;
          startC = c;
          break;
        }
      }
    }

    const array<pair<int, int>, 4> directions{
        {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

    // BFS with {startX, startC} from the start.
    queue<pair<int, int>> frontier;
    frontier.emplace(startR, startC);
    grid[startR][startC] = 'X';

    int distance = 0;
    while (!frontier.empty()) {
      size_t frontierSize = frontier.size();
      while (frontierSize--) {
        const auto [currR, currC] = frontier.front();
        frontier.pop();

        // Do goal-checks before adding to the frontier.
        for (const auto& [dr, dc] : directions) {
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
