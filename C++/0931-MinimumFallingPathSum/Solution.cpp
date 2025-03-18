#include <algorithm>
#include <climits>
#include <vector>

class Solution {
 public:
  int minFallingPathSum(std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    // At the beginning of the i-th iteration, prevRow[j] represents the minimum
    // falling path sum so far if matrix[i-1][j] is picked
    // There are only three choices: Diagonally left/right or directly above
    std::vector<int> prevRow = matrix[0];
    for (int i = 1; i < rows; ++i) {
      std::vector<int> currRow(cols);

      // Initialize the first and last element to simplify loop and avoid
      // checking for out-of-bounds
      currRow[0] =
          std::min(prevRow[0], cols > 1 ? prevRow[1] : INT_MAX) + matrix[i][0];
      currRow[cols - 1] =
          std::min(prevRow[cols - 1], cols > 1 ? prevRow[cols - 2] : INT_MAX) +
          matrix[i][cols - 1];

      for (int j = 1; j < cols - 1; ++j) {
        currRow[j] =
            std::min(prevRow[j - 1], std::min(prevRow[j], prevRow[j + 1])) +
            matrix[i][j];
      }

      // avoid copy
      prevRow = std::move(currRow);
    }

    return *std::min_element(prevRow.begin(), prevRow.end());
  }
};
