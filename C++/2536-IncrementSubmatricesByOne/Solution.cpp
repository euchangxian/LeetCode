#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> rangeAddQueries(
      int n,
      std::vector<std::vector<int>>& queries) {
    // n x n matrix with 0s initially.
    // queries[i] = [row1, col1, row2, col2] => add 1 to every element in the
    // submatrix with top-left (row1, col1), bottom-right (row2, col2)
    // Difference array, line-sweepy.
    std::vector<std::vector<int>> diff(n + 1, std::vector<int>(n + 1, 0));

    for (const auto& query : queries) {
      int row1 = query[0], col1 = query[1], row2 = query[2], col2 = query[3];
      for (int r = row1; r <= row2; ++r) {
        ++diff[r][col1];
        --diff[r][col2 + 1];
      }
    }

    std::vector<std::vector<int>> grid(n, std::vector<int>(n, 0));
    for (int r = 0; r < n; ++r) {
      int pref = 0;
      for (int c = 0; c < n; ++c) {
        pref += diff[r][c];

        grid[r][c] = pref;
      }
    }
    return grid;
  }
};
