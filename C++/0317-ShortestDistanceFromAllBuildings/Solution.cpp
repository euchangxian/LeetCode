#include <algorithm>
#include <array>
#include <climits>
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
  int shortestDistance(std::vector<std::vector<int>>& grid) {
    // Suppose we BFS from houses to empty cells instead. Then, at each cell
    // (r, c), we maintain (totalDistance, reachableHouses).
    // This achieves the same time complexity.
    //
    // However, we can prune based off this reversed perspective.
    // Notice that we need all houses to be reachable. Thus in each BFS, if
    // a cell is not reachable, then subsequent BFS do not need to explore
    // any paths through this cell.
    //
    // This can be implemented by maintaining the iteration counter and mutating
    // the input grid, such that if the houses is 1, then we only consider cells
    // that are reachable so-far by 0 houses.
    // If houses=2, then consider cells reachable by 1 house (can be represented
    // by grid[i][j] == -1)
    //
    // By doing this, we remove the preprocessing step to find the number of
    // houses, and also prune effectively.
    const int m = grid.size();
    const int n = grid[0].size();

    std::vector<std::vector<int>> total(m, std::vector<int>(n, 0));

    int houses = 0;
    auto bfs = [m, n, &grid, &total, &houses](int i, int j) -> int {
      const int EMPTY = -houses;
      int minTotal = INT_MAX;
      std::queue<std::pair<int, int>> frontier;
      frontier.emplace(i, j);

      int steps = 1;
      while (!frontier.empty()) {
        int sz = frontier.size();
        while (sz--) {
          auto [r, c] = frontier.front();
          frontier.pop();

          for (const auto [dr, dc] : directions) {
            int nr = r + dr;
            int nc = c + dc;

            // prune out of bounds, obstacles, houses, cells that are not
            // reachable (or already seen)
            if (nr < 0 || nc < 0 || nr >= m || nc >= n || grid[nr][nc] == 2 ||
                grid[nr][nc] == 1 || grid[nr][nc] != EMPTY) {
              continue;
            }

            total[nr][nc] += steps;
            minTotal = std::min(minTotal, total[nr][nc]);

            --grid[nr][nc];  // also marks as visited.
            frontier.emplace(nr, nc);
          }
        }
        ++steps;
      }

      ++houses;  // incremented for next BFS.
      return minTotal;
    };

    int result = INT_MAX;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          // No std::min.
          // Each house discovered causes the previous value to be invalid.
          result = bfs(i, j);
        }
      }
    }
    return result == INT_MAX ? -1 : result;
  }

  int shortestDistanceNaive(std::vector<std::vector<int>>& grid) {
    // m x n grid of values 0, 1 or 2.
    // 0: empty land
    // 1: building, cannot pass through
    // 2: obstacle, cannot pass through.
    // Build a house on an empty land that reaches all buildings in the
    // shortest travel distance.
    // m,n <= 50 ---> m x n <= 2500
    // nm vertices, 4nm edges.
    //
    // Hm? Does travel distance means the path cannot go through the obstacle?
    // I guess so.
    // Naively, Run BFS on all '0' nodes to determine the shortest distance to
    // all buildings, then take the best sum.
    // Potentially O(V*(V+E)), which should be AC-ed without TLE.
    //
    // How can we do better?
    const int m = grid.size();
    const int n = grid[0].size();

    int buildings = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          ++buildings;
        }
      }
    }

    auto bfs = [m, n, buildings, &grid](int i, int j) -> int {
      std::queue<std::pair<int, int>> frontier;
      std::vector<int> dist(m * n, INT_MAX);

      frontier.emplace(i, j);
      dist[i * n + j] = 0;

      int total = 0;
      int reachable = 0;
      while (!frontier.empty()) {
        auto [r, c] = frontier.front();
        frontier.pop();

        int curr = r * n + c;
        if (grid[r][c] == 1) {
          ++reachable;
          total += dist[curr];  // add distance to this building.
          continue;
        }

        for (const auto [dr, dc] : directions) {
          int nr = r + dr;
          int nc = c + dc;

          int next = nr * n + nc;
          if (nr < 0 || nc < 0 || nr >= m || nc >= n || grid[nr][nc] == 2 ||
              dist[next] != INT_MAX) {
            continue;
          }

          dist[next] = dist[curr] + 1;
          frontier.emplace(nr, nc);
        }
      }

      return reachable == buildings ? total : INT_MAX;
    };

    int result = INT_MAX;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 0) {
          result = std::min(result, bfs(i, j));
        }
      }
    }
    return result == INT_MAX ? -1 : result;
  }
};
