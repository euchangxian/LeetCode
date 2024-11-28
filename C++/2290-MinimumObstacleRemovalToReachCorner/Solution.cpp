#include <array>
#include <cstddef>
#include <deque>
#include <functional>
#include <queue>
#include <vector>

class Solution {
 private:
  static constexpr int INF = 10e5;  // m * n <= 10e5
  static constexpr std::array<std::array<int, 2>, 4> directions = {{
      {0, 1},
      {1, 0},
      {0, -1},
      {-1, 0},
  }};

 public:
  int minimumObstacles(std::vector<std::vector<int>>& grid) {
    // BFS would work. Given that edges are unweighted.
    // NOT NAIVE BFS.
    // 0/1 BFS with a Deque.
    // The edges are not exactly unweighted. Cost of moving to an empty cell
    // is 0, while the cost of moving to a Cell with an obstacle is 1.
    // We want to explore the "free" edges first. Hence, a priority_queue may
    // be helpful. But we can further optimize to use a Deque instead.
    const size_t rows = grid.size();
    const size_t cols = grid[0].size();

    // {obstaclesRemoved, row, col}
    std::deque<std::array<int, 3>> frontier;

    // necessary to prune cells.
    // Not the actual manhattan distance, but the number of obstacles in the
    // path to cell (i, j) so far.
    std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, INF));

    frontier.push_front({0, 0, 0});
    dist[0][0] = 0;

    while (!frontier.empty()) {
      auto [obstacles, r, c] = frontier.front();
      frontier.pop_front();

      if (r == rows - 1 && c == cols - 1) {
        // early return is possible with this 0/1 BFS.
        return obstacles;
      }

      for (const auto [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr >= rows || nc >= cols ||
            obstacles + grid[nr][nc] >= dist[nr][nc]) {
          continue;
        }

        dist[nr][nc] = obstacles + grid[nr][nc];

        // If the edge is 0, i.e., no obstacle, then push to front. Else
        // push to back. This maintains the priority_queue-like behavior where
        // we explore cheaper cells greedily.
        if (grid[nr][nc] == 0) {
          frontier.push_front({obstacles, nr, nc});
        } else {
          frontier.push_back({obstacles + 1, nr, nc});
        }
      }
    }

    // std::unreachable(), C++23
    return -1;
  }

  int minimumObstaclesDijkstra(std::vector<std::vector<int>>& grid) {
    const size_t rows = grid.size();
    const size_t cols = grid[0].size();

    std::vector<std::vector<int>> distances(rows, std::vector<int>(cols, INF));

    // {numberOfObstaclesInPath, row, col}
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>, std::greater<>>
        minHeap;

    distances[0][0] = 0;
    minHeap.emplace(0, 0, 0);
    while (!minHeap.empty()) {
      auto [count, r, c] = minHeap.top();
      minHeap.pop();

      if (r == rows - 1 && c == cols - 1) {
        break;
      }

      for (const auto& [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr >= rows || nc >= cols ||
            count + grid[nr][nc] >= distances[nr][nc]) {
          continue;
        }

        distances[nr][nc] = count + grid[nr][nc];
        minHeap.emplace(count + grid[nr][nc], nr, nc);
      }
    }

    return distances[rows - 1][cols - 1];
  }
};
