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
  vector<pair<int, int>> const directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  void dfs(vector<vector<int>> const &heights, vector<vector<bool>> &seen,
           int r, int c) {
    seen[r][c] = true;
    for (auto const &[dr, dc] : directions) {
      int nr = r + dr;
      int nc = c + dc;

      // if not valid index, or already visited, or has a lower height than the
      // current, ignore
      if (nr < 0 || nc < 0 || nr >= heights.size() || nc >= heights[0].size() ||
          seen[nr][nc] || heights[nr][nc] < heights[r][c]) {
        continue;
      }
      dfs(heights, seen, nr, nc);
    }
  }

public:
  vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
    // Top right, bottom left corner are always in the answer, as they are
    // adjacent to both the Pacific and Atlantic Ocean.
    // DFS/BFS
    int rows = heights.size();
    int cols = heights[0].size();

    vector<vector<bool>> pacific(rows, vector<bool>(cols, false));
    vector<vector<bool>> atlantic(rows, vector<bool>(cols, false));

    for (int c = 0; c < cols; ++c) {
      // DFS from the top-edge, mark cells that can reach the Pacific ocean
      dfs(heights, pacific, 0, c);

      // DFS from bottom edge, mark cells that can reach the Atlantic
      dfs(heights, atlantic, rows - 1, c);
    }

    for (int r = 0; r < rows; ++r) {
      // DFS from left edge to mark cells that can reach the Pacific
      dfs(heights, pacific, r, 0);

      // DFS from right edge to mark cells that can reach the Atlantic
      dfs(heights, atlantic, r, cols - 1);
    }

    // Get the intersection of cells that are marked true in both pacific and
    // atlantic i.e., can reach both sides
    vector<vector<int>> result;
    result.reserve(rows * cols);
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        if (pacific[r][c] && atlantic[r][c]) {
          result.push_back({r, c});
        }
      }
    }
    return result;
  }
};
