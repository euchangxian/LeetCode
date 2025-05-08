#include <algorithm>
#include <array>
#include <functional>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

constexpr int INF = 2E9;
class Solution {
 public:
  int minTimeToReach(std::vector<std::vector<int>>& moveTime) {
    // moveTime[i][j] represents the minimum time in second when you can START
    // moving to that room.
    // Start at (0, 0), only move to adjacent rooms. Traversing an edge takes
    // 1 second.
    // Return the minimum time to reach (n-1, m-1).
    // Feels like Dijkstra, where depending on the earliest time we reach a
    // cell, the edges have different weights.
    // Can we do better?
    // 0/1 BFS? If we are forced to explore a cell at a late time, technically
    // other cells are 0-cost.
    // But for the other scenarios? Not sure. Don't have a strong intuition for
    // 0/1 BFS.
    const int n = moveTime.size();
    const int m = moveTime[0].size();

    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>, std::greater<>>
        pq;
    std::vector<std::vector<int>> dist(n, std::vector<int>(m, INF));
    pq.emplace(0, 0, 0);
    dist[0][0] = 0;
    while (!pq.empty()) {
      auto [d, r, c] = pq.top();
      pq.pop();

      if (r == n - 1 && c == m - 1) {
        return d;
      }

      if (d > dist[r][c]) {
        continue;  // prune outdated nodes
      }

      for (const auto [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr >= n || nc >= m) {
          continue;
        }

        int nextTime = std::max(dist[r][c], moveTime[nr][nc]) + 1;
        if (nextTime >= dist[nr][nc]) {
          continue;
        }
        pq.emplace(nextTime, nr, nc);
        dist[nr][nc] = nextTime;
      }
    }

    // target is always reachable.
    std::unreachable();
  }
};
