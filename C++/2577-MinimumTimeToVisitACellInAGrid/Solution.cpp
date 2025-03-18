#include <array>
#include <cstddef>
#include <cstdlib>
#include <functional>
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
  int minimumTime(std::vector<std::vector<int>>& grid) {
    // seems like 778.Swim in Rising Water
    // grid[row][col] represents the minimum time to be able to visit the cell
    // (row, col).
    // Each move is a time-step.
    // i.e., t=0, start at (0, 0)
    //       t=1, Can go to (0, 1), if grid[0][1] <= 1.
    //
    // Must make a move at each time step, return -1 if not possible.
    // Minimum time to reach bottom right.
    //
    // In the optimal path, cells can be revisited. Naive BFS may not work.
    // We want to explore based on a heuristics, otherwise it becomes a search
    // tree of width 4.
    //
    // Therefore, we need to store {time, row, col} at the minimum, indicating
    // what time we visited this (row, col). We also can not prune cells that
    // were visited earlier, since we may need to move to that cell in a later
    // time.
    // Dijkstra.
    //
    // OKAY. First, instead of "revisiting" cells, like actually re-adding cells
    // into the frontier, observe that so-long as there is a valid move from
    // (0, 0) to its neighbours (0, 1) or (1, 0), we can always "wait" till
    // we can visit the next cell.
    // E.g., at (0, 1), t = 1
    //       grid[0][2] = 3, and cannot be visited directly yet.
    //
    // Therefore, we can simulate a "wait" by moving back to (0, 0) at t=2,
    // then back to (0, 1) at t=3, and then (0, 2) at t=4.
    // Notice that the waiting time depends on the difference between the
    // current time and grid[r][c].
    // If the difference > 1, depending on the parity, if odd, we can visit the
    // cell on time, and if even, +1 second after.
    // This is because each "wait" unit is 2-seconds, then +1 for the travel
    // time to that cell.
    //
    // By realizing this, we can effectively "visit" cells only once.
    // This allows us to prune cells that were already visited earlier.
    if (grid[0][1] > 1 && grid[1][0] > 1) {
      // Impossible to move to end, if no moves can be made at the start.
      return -1;
    }

    using Node = std::array<int, 3>;

    const std::size_t m = grid.size();
    const std::size_t n = grid[0].size();

    // represents the minimum time to reach the cell.
    std::vector<std::vector<char>> visited(m, std::vector<char>(n, false));
    std::priority_queue<Node, std::vector<Node>, std::greater<>> frontier;
    frontier.push({0, 0, 0});
    visited[0][0] = true;

    while (!frontier.empty()) {
      const auto [time, r, c] = frontier.top();
      frontier.pop();

      if (r == m - 1 && c == n - 1) {
        return time;
      }

      // Copy-by-value 8 bytes (4 bytes integers),
      // vs
      // copy-by-reference 16 bytes address
      for (const auto [dr, dc] : directions) {
        const int nr = r + dr;
        const int nc = c + dc;
        if (nr < 0 || nc < 0 || nr >= m || nc >= n || visited[nr][nc]) {
          continue;
        }
        visited[nr][nc] = true;

        // Calculate the difference, take the parity: if even diff, then +1,
        // and the nextTime will be grid[nr][nc] + waitTime.
        int waitTime = (grid[nr][nc] - time) % 2 == 0 ? 1 : 0;
        int nextTime = std::max(time + 1, waitTime + grid[nr][nc]);
        frontier.push({nextTime, nr, nc});
      }
    }

    // The only time where the bottom right is unreachable, is when the cells
    // adjacent to the start point (0, 0) is not reachable in one time-step.
    // In every other case, we can wait indefinitely by moving back and forth
    // before visiting the next cell.
    std::unreachable();
  }
};
