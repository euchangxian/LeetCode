#include <algorithm>
#include <cstddef>
#include <vector>

class Solution {
 public:
  int countSquares(std::vector<std::vector<int>>& matrix) {
    // Seems similar to LC 221 - Maximal Square, except instead of determining
    // the largest square, count the number of squares with '1's.
    // Let dp[i][j] represent the count of squares with their right-corner
    // ending at (i, j).
    const std::size_t rows = matrix.size();
    const std::size_t cols = matrix[0].size();

    std::vector<std::vector<int>> dp(rows + 1, std::vector<int>(cols + 1, 0));

    int count = 0;
    for (std::size_t i = 1; i <= rows; ++i) {
      for (std::size_t j = 1; j <= cols; ++j) {
        if (matrix[i - 1][j - 1] == 0) {
          continue;
        }

        // Determine the would-be length of the square formed with cell (i, j)
        // as the bottom-right corner.
        // This can be derived from the count of the squares at the diagonal,
        // left, right of (i, j).
        // e.g., if count is 1, then the size of the square must be 1.
        // if count is 5, then the size of the square must be 2.
        // Ok. The formula seems to be less straightforward to derive.
        // JK. Just consider the number of possible squares with its
        // bottom-right corner as (i, j). This means that there could be
        // 1, 2, 3, ... squares of length 1, 2, 3, .. correspondingly.
        // Simply take the minimum.
        dp[i][j] = 1 + std::min(dp[i - 1][j - 1],
                                std::min(dp[i - 1][j], dp[i][j - 1]));
        count += dp[i][j];
      }
    }

    return count;
  }
};
