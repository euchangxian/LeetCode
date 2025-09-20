#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
class Solution {
 public:
  std::vector<std::vector<int>> matrixRankTransform(
      std::vector<std::vector<int>>& matrix) {
    // Return m * n matrix answer, where answer[row][col] is the rank of
    // matrix[row][col].
    // The rank of an element is how large it is compared to other elements.
    // - Starts from 1
    // - If two elements p and q are in the same row/column, then:
    //   - if p < q, then rank(p) < rank(q)
    //   - if p == q, then rank(p) == rank(q)
    //   - if p > q, then rank(p) > rank(q)
    // The rank should be as small as possible, i.e., compacted.
    //
    // 1 <= m, n <= 500
    // -10^9 <= matrix[r][c] <= 10^9
    // Based off these inputs, m * n <= 2.5 * 10^5 => mnlog(mn) solution.
    // Something related to sorting? Collect all cells, sort in ascending order.
    // How to determine the rank relative to elements in the same row/columns?
    // Different values may be assigned different ranks, so we cant statically
    // assign ranks to the values after sorting.
    //
    // Maintain the current maximum of the row/column? Along with the
    // corresponding rank of that maximum. Since we have already sorted in
    // ascending order, we just have to assign the same rank if the element is
    // equal to the maximum. +1 rank if greater.

    const std::size_t m = matrix.size();
    const std::size_t n = matrix[0].size();

    // {value, row, col}
    std::vector<std::array<int, 3>> cells;
    cells.reserve(m * n);
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        cells.push_back({matrix[r][c], r, c});
      }
    }

    std::sort(cells.begin(), cells.end());

    // {max, rank}
    std::vector<std::array<int, 2>> rowMax(m, {0, 0});
    std::vector<std::array<int, 2>> colMax(n, {0, 0});
    for (auto [val, r, c] : cells) {
      auto [rowVal, rowRank] = rowMax[r];
      auto [colVal, colRank] = colMax[c];

      // if greater, then simply update to 1 + max of the row/col ranks.
      if (val > rowVal && val > colVal) {
        matrix[r][c] = std::max(rowRank, colRank) + 1;
        rowMax[r][0] = val;
        rowMax[r][1] = matrix[r][c];

        colMax[c][0] = val;
        colMax[c][1] = matrix[r][c];
        continue;
      }

      // Otherwise, a little more complicated. The remaining cases are:
      // 1. Equal to both row and col max. In that case, the ranks should be
      //    equal.
      // 2. Equal to only row OR col max. In that case, update the rank to match
      //    the greater one. This would still satisfy the constraints of
      //    p > q => rank(p) > rank(q)
      if (val == rowVal && val == colVal) {
        matrix[r][c] = rowRank;  // both row and colRank should be the same.
        // no need to update row/colMax
        continue;
      }

      // Otherwise, update to the greater rank
      matrix[r][c] = std::max(rowRank, colRank);
      rowMax[r][0] = val;
      rowMax[r][1] = matrix[r][c];

      colMax[c][0] = val;
      colMax[c][1] = matrix[r][c];
    }
    return matrix;
  }
};
