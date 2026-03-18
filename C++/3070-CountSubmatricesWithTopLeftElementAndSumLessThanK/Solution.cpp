#include <vector>

class Solution {
 public:
  int countSubmatrices(std::vector<std::vector<int>>& grid, int k) {
    // return the number of submatrices that contain the top-left element
    // and have a sum <= k.
    //
    // 2D prefix sums.
    // Iterate over cells, treating them as bottom-right of the submatrix.
    // Check top and left.
    const int m = static_cast<int>(grid.size());
    const auto n = static_cast<int>(grid[0].size());

    auto result = 0;
    std::vector<int> colSum(n, 0);
    for (const auto& row : grid) {
      auto submatrixSum = 0;
      for (auto c = 0; c < n; ++c) {
        colSum[c] += row[c];

        // include top-left
        submatrixSum += colSum[c];

        result += submatrixSum <= k;
      }
    }
    return result;
  }
};
