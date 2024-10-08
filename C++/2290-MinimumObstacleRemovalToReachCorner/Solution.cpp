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

using namespace std;
class Solution {
 private:
  int const INF = 10e5;  // m * n <= 10e5
  vector<pair<int, int>> const directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

 public:
  int minimumObstacles(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> distances(rows, vector<int>(cols, INF));

    // {numberOfObstaclesInPath, row, col}
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                   greater<>>
        minHeap;

    distances[0][0] = 0;
    minHeap.emplace(0, 0, 0);
    while (!minHeap.empty()) {
      auto [count, r, c] = minHeap.top();
      minHeap.pop();

      if (r == rows - 1 && c == cols - 1) {
        break;
      }

      for (auto const& [dr, dc] : directions) {
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
