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
  vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

 public:
  void islandsAndTreasure(vector<vector<int>>& grid) {
    int const INF = INT_MAX;
    int m = grid.size();
    int n = grid[0].size();

    // BFS from each Treasure cell. If not '-1' or '0', then update to min
    int landCells = 0;
    queue<pair<int, int>> frontier;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == INF) {
          ++landCells;
          continue;
        }
        if (grid[i][j] == 0) {
          frontier.push({i, j});
        }
      }
    }

    int dist = 0;
    while (!frontier.empty()) {
      int size = frontier.size();
      ++dist;

      for (int i = 0; i < size; ++i) {
        auto [r, c] = frontier.front();
        frontier.pop();

        for (auto const& [dr, dc] : directions) {
          int nr = r + dr;
          int nc = c + dc;

          if (nr < 0 || nc < 0 || nr >= m || nc >= n || grid[nr][nc] == -1 ||
              grid[nr][nc] == 0 || grid[nr][nc] <= dist) {
            continue;
          }
          grid[nr][nc] = dist;
          frontier.push({nr, nc});
        }
      }
    }
  }
};
