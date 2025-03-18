#include <algorithm>
#include <vector>

class Solution {
 public:
  int maximalSquare(std::vector<std::vector<char>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // dp[i][j] represents the maximum size of the square that can be formed
    // with (i, j) as the bottom-right cell of the would-be square.
    int maxSize = 0;
    std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 0));
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        // base-cases
        if (i == 0 || j == 0 || matrix[i][j] == '0') {
          // equivalent to 1 - 0 or 0 - 0
          dp[i][j] = matrix[i][j] - '0';
          maxSize = std::max(maxSize, dp[i][j]);
          continue;
        }

        // left, up, diagonal
        dp[i][j] =
            std::min(dp[i - 1][j - 1], std::min(dp[i][j - 1], dp[i - 1][j])) +
            1;
        maxSize = std::max(maxSize, dp[i][j]);
      }
    }

    return maxSize * maxSize;
  }
};
