#include <array>
#include <vector>

constexpr int MOD = 1e9 + 7;

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

class Solution {
 public:
  int countPaths(std::vector<std::vector<int>>& grid) {
    // Topo sort. Count paths in DAG.
    const int m = grid.size();
    const int n = grid[0].size();

    std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
    int answer = 0;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        answer = (1LL * answer + dfs(grid, memo, r, c)) % MOD;
      }
    }

    return answer;
  }

 private:
  int dfs(std::vector<std::vector<int>>& grid,
          std::vector<std::vector<int>>& memo,
          int r,
          int c) {
    int& ans = memo[r][c];
    if (ans != -1) {
      return ans;
    }

    ans = 1;
    for (const auto [dr, dc] : directions) {
      int nr = r + dr;
      int nc = c + dc;

      if (nr < 0 || nc < 0 || nr >= grid.size() || nc >= grid[0].size()) {
        continue;
      }

      if (grid[r][c] < grid[nr][nc]) {
        ans = (1LL * ans + dfs(grid, memo, nr, nc)) % MOD;
      }
    }
    return ans;
  }
};
