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
public:
  int orangesRotting(vector<vector<int>> &grid) {
    // BFS from each rotten orange. Count iterations
    int m = grid.size();
    int n = grid[0].size();

    int freshOranges = 0;
    queue<pair<int, int>> frontier;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          ++freshOranges;
        } else if (grid[i][j] == 2) {
          frontier.push({i, j});
        }
      }
    }

    if (freshOranges <= 0) {
      return 0;
    }

    // R, D, L, U
    vector<pair<int, int>> const directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int time = 0;
    while (!frontier.empty() && freshOranges > 0) {
      ++time;
      int k = frontier.size();
      for (int i = 0; i < k && freshOranges > 0; ++i) {
        auto [r, c] = frontier.front();
        frontier.pop();

        for (auto const &[dr, dc] : directions) {
          int nr = r + dr;
          int nc = c + dc;

          if (nr < 0 || nr >= m || nc < 0 || nc >= n || grid[nr][nc] == 0 ||
              grid[nr][nc] == 2) {
            continue;
          }

          grid[nr][nc] = 2; // mark as rotten
          frontier.push({nr, nc});
          --freshOranges;
        }
      }
    }

    if (freshOranges > 0) {
      // Consider the case where the only rotten orange is not adjacent to any
      // fresh orange
      return -1;
    }

    return time;
  }
};
