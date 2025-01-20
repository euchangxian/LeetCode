#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

class Solution {
 public:
  int firstCompleteIndex(std::vector<int>& arr,
                         std::vector<std::vector<int>>& mat) {
    // m x n 2D mat
    // arr.size = m * n
    // Both contain all the integers in the range [1..m * n]
    // Go through each index i in arr and paint the cell in mat containing
    // the integer arr[i].
    // Return the smallest index i at which a row or column will be completely
    // painted in mat.
    //
    // HMMM. Naively, after painting a cell, check its row/column. Costly
    // though. Can we do better?
    // Maintain a row/column count? Since we are visiting distinct cells.
    //
    // Next, finding the respective cell in mat, i.e., mapping arr to mat.
    // O(m * n) preprocess.
    const int m = mat.size();
    const int n = mat[0].size();
    std::vector<std::pair<int, int>> mapping(m * n + 1);
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        mapping[mat[r][c]] = {r, c};
      }
    }

    // Count number of cells in row/column that have been painted.
    std::vector<int> rowCount(m, 0);
    std::vector<int> colCount(n, 0);

    for (int i = 0; i < m * n; ++i) {
      auto [r, c] = mapping[arr[i]];

      // if rowCount == columns, or colCount == rows
      if (++rowCount[r] == n || ++colCount[c] == m) {
        return i;
      }
    }

    return -1;  // unreachable.
  }
};
