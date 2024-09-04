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
using pii = pair<int, int>;
using tii = tuple<int, int, int>;
class Solution {
private:
  int const INF = 10e6;
  vector<pii> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

public:
  int minimumEffortPath(vector<vector<int>> &heights) {
    int rows = heights.size();
    int cols = heights[0].size();

    vector<vector<int>> efforts(rows, vector<int>(cols, INF));

    // {effort, row, col}
    priority_queue<tii, vector<tii>, greater<>> minHeap;

    efforts[0][0] = 0;
    minHeap.emplace(0, 0, 0);

    while (!minHeap.empty()) {
      auto [effort, r, c] = minHeap.top();
      minHeap.pop();

      if (r == rows - 1 && c == cols - 1) {
        break;
      }

      for (auto const &[dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) {
          continue;
        }

        // Not the sum of efforts, but the max difference in the route
        int nextEffort = max(effort, abs(heights[r][c] - heights[nr][nc]));
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
