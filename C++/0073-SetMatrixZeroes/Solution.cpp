#include <vector>

class Solution {
 public:
  void setZeroes(std::vector<std::vector<int>>& matrix) {
    const int rows = matrix.size();
    const int cols = matrix[0].size();
    std::vector<bool> zeroRows(rows);
    std::vector<bool> zeroCols(cols);

    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        if (matrix[r][c]) {
          continue;
        }
        zeroRows[r] = true;
        zeroCols[c] = true;
      }
    }

    for (int r = 0; r < rows; ++r) {
      if (!zeroRows[r]) {
        continue;
      }

      for (int c = 0; c < cols; ++c) {
        matrix[r][c] = 0;
      }
    }

    for (int c = 0; c < cols; ++c) {
      if (!zeroCols[c]) {
        continue;
      }
      for (int r = 0; r < rows; ++r) {
        matrix[r][c] = 0;
      }
    }
  }
};
