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

constexpr int IMPOSSIBLE = -1;
constexpr int ALWAYS_POSSIBLE = 1e9;

class Solution {
 public:
  int maximumMinutes(std::vector<std::vector<int>>& grid) {
    // 0 represents grass, 1 represents fire, 2 represents wall.
    // Start at top-left (0, 0), destination at bottom-right (m-1, n-1).
    // Move to adjacent every minute.
    // Similarly, every fire cell spreads to adjacent cells that are not walls.
    // Return the maximum number of minutes you can wait in initial position,
    // while still being able to reach the safehouse.
    // If impossible, return -1. If always possible, return 10^9
    //
    // BFS from all fire nodes to determine at which minute will each cell be
    // consumed by fire.
    // Thus, we get a new Graph. How can we then model this graph to solve our
    // problem?
    //
    // Given that we only need a PATH, not the SHORTEST PATH, we just need to
    // determine connectivity between the start and the end. Union Find?
    // Check for connectivity? Hm. Probably unite descending times?
    // If there is no path, then we continue uniting.
    // If there is, then we can return that time as the answer?
    //
    // Hm. Doesnt seem correct too. Need the shortest time for the person to
    // reach a particular cell, too. BFS?
    // Then, if the persons arrival time is < than the fire's arrival time,
    // the person can traverse to that cell.
    // Apart for the final destination cell, which uses <=.
    // Then, a valid path from src to destination is one where all cells have
    // time_fire - time_person > 0 (or time_person - time_fire < 0)

    const int m = grid.size();
    const int n = grid[0].size();
    std::vector<std::vector<int>> ptime(m, std::vector<int>(n, -1));
    std::vector<std::vector<int>> ftime(m, std::vector<int>(n, -1));

    auto bfs = [&grid, m, n](auto& time, bool isFire) {
      std::queue<std::pair<int, int>> frontier;
      if (!isFire) {
        frontier.emplace(0, 0);
        grid[0][0] = 0;
      } else {
        for (int r = 0; r < m; ++r) {
          for (int c = 0; c < n; ++c) {
            if (grid[r][c] == 1) {
              frontier.emplace(r, c);
              grid[r][c] = 0;
            }
          }
        }
      }

      while (!frontier.empty()) {
        auto [r, c] = frontier.front();
        frontier.pop();

        for (const auto [dr, dc] : directions) {
          int nr = r + dr;
          int nc = c + dc;

          if (nr < 0 || nc < 0 || nr >= m || nc >= n || grid[nr][nc] == 2 ||
              time[nr][nc] != -1) {
            continue;
          }

          time[nr][nc] = time[r][c] + 1;
          frontier.emplace(nr, nc);
        }
      }
    };

    bfs(ptime, false);
    bfs(ftime, true);

    if (ptime[m - 1][n - 1] == -1) {
      return IMPOSSIBLE;
    }
    if (ftime[m - 1][n - 1] == -1) {
      return ALWAYS_POSSIBLE;
    }
    if (ftime[m - 1][n - 1] < ptime[m - 1][n - 1]) {
      return IMPOSSIBLE;
    }

    // NOTE: This part is quite smart. Observe that we do not have to perform
    // any sort of path exploration from start to destination.
    // This is because if the fire is "behind" us, then it will never catch up.
    // Whereas if it is "in-front" of us, we will never make it in time.
    // Thus, we only need to check the cell directly above, and directly to the
    // left of the destination cell, to determine the longest waiting time,
    // which is itself bounded by the difference in the arrival time at the
    // destination cell.
    // WLOG, consider a path that reaches the destination from the cell above.
    // Let the difference in arrival time, diffTop = ftop - ptop.
    // Thus, if diffTop > diffDest, then we are not bounded by any cells in
    // the path. Our answer is thus bounded by the arrival time at the
    // destination: diffDest.
    // Otherwise, diffTop <= diffDest, which means that we need to reach the
    // adjacent cells 1 minute earlier. (this is the earlier edge case, where
    // except for the destination cell, ptime < ftime for all other cells to
    // be valid)
    int maxWait = ftime[m - 1][n - 1] - ptime[m - 1][n - 1];

    int ptop = ptime[m - 2][n - 1];
    int pleft = ptime[m - 1][n - 2];

    int ftop = ftime[m - 2][n - 1];
    int fleft = ftime[m - 1][n - 2];

    if ((ptop > -1 && ftop - ptop > maxWait) ||
        (pleft > -1 && fleft - pleft > maxWait)) {
      return maxWait;
    }
    return maxWait - 1;
  }
};
