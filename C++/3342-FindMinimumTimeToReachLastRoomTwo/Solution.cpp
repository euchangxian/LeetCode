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
    // Same as 3341. Find Minimum Time To Reach Last Room One, except moving
    // between adjacent room takes one second for one move, two seconds for the
    // next, alternating.
    // Need to be careful when pruning.
    const int n = moveTime.size();
    const int m = moveTime[0].size();

    // isEven indicate next step will be 2 cost
    // {time, isEven, r, c}
    using State = std::tuple<int, int, int, int>;
    std::priority_queue<State, std::vector<State>, std::greater<>> pq;
    std::vector<std::vector<int>> dist(n, std::vector<int>(m, INF));
    dist[0][0] = 0;
    pq.emplace(0, false, 0, 0);

    while (!pq.empty()) {
      auto [time, isEven, r, c] = pq.top();
      pq.pop();

      if (r == n - 1 && c == m - 1) {
        return time;
      }

      if (time > dist[r][c]) {
        continue;
      }

      for (const auto [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr >= n || nc >= m) {
          continue;
        }

        int nextTime = std::max(dist[r][c], moveTime[nr][nc]) + (1 + isEven);
        if (nextTime >= dist[nr][nc]) {
          continue;
        }
        pq.emplace(nextTime, !isEven, nr, nc);
        dist[nr][nc] = nextTime;
      }
    }

    // Destination is always reachable in a finite amount of time.
    std::unreachable();
  }
};
