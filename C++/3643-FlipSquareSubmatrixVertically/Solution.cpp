#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>>
  reverseSubmatrix(std::vector<std::vector<int>>& grid, int x, int y, int k) {
    // given m*n integer matrix.
    // x, y represents the row, column indices of the top-left corner of a
    // k*k square submatrix.
    // Flip the submatrix by reversing the order of its vertically.
    for (int r = 0; r < k / 2; ++r) {
      for (int c = y; c < y + k; ++c) {
        std::swap(grid[r + x][c], grid[x + k - 1 - r][c]);
      }
    }

    return grid;
  }
};
