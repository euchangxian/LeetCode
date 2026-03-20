#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> minAbsDiff(std::vector<std::vector<int>>& grid,
                                           int k) {
    // m x n integer matrix and integer k.
    // For every kxk submatrix of grid, compute minimum absolute difference
    // between any two distinct values within that submatrix.
    // Return a 2D array of size (m-k+1)*(n-k+1), where
    // ans[i][j] is the minimum difference in the submatrix whose top-left
    // corner is (i, j) in grid.
    //
    // - distinct values.
    // - k*k submatrix i.e., square.
    //
    // Just brute-force.
    constexpr int INF = 1E9;
    const auto m = static_cast<int>(grid.size());
    const auto n = static_cast<int>(grid[0].size());
    const auto kk = k * k;

    std::vector<std::vector<int>> result(m - k + 1,
                                         std::vector<int>(n - k + 1));

    std::vector<int> submatrix;
    submatrix.reserve(m * n);
    for (int r = 0; r < m - k + 1; ++r) {
      for (int c = 0; c < n - k + 1; ++c) {
        for (int i = r; i < r + k; ++i) {
          for (int j = c; j < c + k; ++j) {
            submatrix.push_back(grid[i][j]);
          }
        }
        std::ranges::sort(submatrix);

        auto minDiff = INF;
        for (int i = 1; i < kk; ++i) {
          auto diff = submatrix[i] - submatrix[i - 1];
          if (diff == 0 || diff >= minDiff) {
            continue;
          }
          minDiff = diff;
        }
        result[r][c] = minDiff == INF ? 0 : minDiff;
        submatrix.clear();
      }
    }
    return result;
  }
};
