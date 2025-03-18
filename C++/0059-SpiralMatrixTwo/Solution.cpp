#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> generateMatrix(int n) {
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

    int k = 1;
    int rowStart = 0, colStart = 0, rowEnd = n - 1, colEnd = n - 1;

    while (rowStart <= rowEnd && colStart <= colEnd) {
      // top row, left to right
      for (int col = colStart; col <= colEnd; ++col) {
        matrix[rowStart][col] = k++;
      }
      ++rowStart;

      // right column, top to bottom
      for (int row = rowStart; row <= rowEnd; ++row) {
        matrix[row][colEnd] = k++;
      }
      --colEnd;

      // bottom row, right to left
      if (rowStart <= rowEnd) {
        for (int col = colEnd; col >= colStart; --col) {
          matrix[rowEnd][col] = k++;
        }
      }
      --rowEnd;

      // left col, bottom to up
      if (colStart <= colEnd) {
        for (int row = rowEnd; row >= rowStart; --row) {
          matrix[row][colStart] = k++;
        }
      }
      ++colStart;
    }
    return matrix;
  }
};
