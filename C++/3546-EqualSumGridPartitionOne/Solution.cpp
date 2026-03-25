#include <vector>

class Solution {
 public:
  bool canPartitionGrid(std::vector<std::vector<int>>& grid) {
    // m*n grid of positive integers.
    // Return true if a horizontal or vertical cut can be made such that:
    // - each of the two resulting sections formed by the cut is non-empty,
    // - the sum of the elements in both sections is equal.
    //
    // Prefix Row-Major sums, Prefix Col-Major sums.
    using i64 = long long;
    const auto m = static_cast<int>(grid.size());
    const auto n = static_cast<int>(grid[0].size());

    // Inclusive prefixes
    std::vector<i64> rowPrefix(m);
    std::vector<i64> colPrefix(n);

    for (int r = 0; r < m; ++r) {
      rowPrefix[r] = 0;
      for (int c = 0; c < n; ++c) {
        rowPrefix[r] += grid[r][c];
        colPrefix[c] += grid[r][c];
      }
      if (r > 0) {
        rowPrefix[r] += rowPrefix[r - 1];
      }
    }

    auto total = rowPrefix.back();
    auto half = total / 2;
    if (half * 2 != total) {
      return false;
    }

    for (int r = 0; r < m - 1; ++r) {
      if (rowPrefix[r] == half) {
        return true;
      }
    }

    for (int c = 0; c < n - 1; ++c) {
      if (c > 0) {
        colPrefix[c] += colPrefix[c - 1];
      }

      if (colPrefix[c] == half) {
        return true;
      }
    }
    return false;
  }
};
