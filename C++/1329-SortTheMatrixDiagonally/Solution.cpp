#include <algorithm>
#include <functional>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> diagonalSort(
      std::vector<std::vector<int>>& mat) {
    // Given m x n matrix mat of integers, sort each matrix diagonal in
    // ascending order.
    // Naively, collect all the diagonals. Sort them, then add them back.
    // Seems like this is just pure implementation-pain though.
    // How to iterate over each diagonal?
    // bottom-left to top-right.
    // (0, 0) -> (1, 1) -> (2, 2)
    // (1, 0) -> (2, 1) -> ...
    // (2, 0) -> (3, 1) -> ...
    //
    // (0, 1) -> (1, 2) -> ...
    // (0, 2) -> (1, 3) -> ...
    //
    // Hm... Every diagonal starts at a boundary-cell on the left/top.
    // Thus, there will be (r + c) - 1 diagonals.
    // Ah. Notice (i, j) -> (i+1, j+1).
    // Thus, we can have a unique index for each diagonal i-j
    // Thus, naively, we can iterate once over every cell, adding them to a
    // 2D vector. Handling negatives are trouble-some though doable.
    // Sort each vector, then assign the values back.
    const int m = mat.size();
    const int n = mat[0].size();  // also the offset to add to make positive.

    auto dIdx = [n](int r, int c) -> int { return r - c + n - 1; };
    std::vector<std::vector<int>> diagonals(m + n - 1);

    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        diagonals[dIdx(r, c)].push_back(mat[r][c]);
      }
    }

    // Four ways to re-assign:
    // 1. sort in descending order, so we can iterate in normal order, pop-back.
    // 2. sort in ascending order, iterate in reverse, pop-back.
    // 3. Maintain a vector of pointers.
    // 4. Use a vector of priority_queues.
    for (auto& diagonal : diagonals) {
      std::sort(diagonal.begin(), diagonal.end(), std::greater<>{});
    }
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        int val = diagonals[dIdx(r, c)].back();
        diagonals[dIdx(r, c)].pop_back();
        mat[r][c] = val;
      }
    }
    return mat;
  }
};
