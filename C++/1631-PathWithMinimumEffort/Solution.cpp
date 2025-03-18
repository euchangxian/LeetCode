#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

constexpr int INF = 10e6;
constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

class Solution {
 public:
  int minimumEffortPath(std::vector<std::vector<int>>& heights) {
    int rows = heights.size();
    int cols = heights[0].size();

    std::vector<std::vector<int>> efforts(rows, std::vector<int>(cols, INF));

    // {effort, row, col}
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>, std::greater<>>
        minHeap;

    efforts[0][0] = 0;
    minHeap.emplace(0, 0, 0);

    while (!minHeap.empty()) {
      auto [effort, r, c] = minHeap.top();
      minHeap.pop();

      if (r == rows - 1 && c == cols - 1) {
        break;
      }

      for (const auto [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) {
          continue;
        }

        // Not the sum of efforts, but the max difference in the route
        int nextEffort =
            std::max(effort, std::abs(heights[r][c] - heights[nr][nc]));
        if (nextEffort >= efforts[nr][nc]) {
          continue;
        }

        efforts[nr][nc] = nextEffort;
        minHeap.emplace(nextEffort, nr, nc);
      }
    }

    return efforts[rows - 1][cols - 1];
  }
};
