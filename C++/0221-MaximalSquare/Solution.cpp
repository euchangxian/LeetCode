#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // dp[i][j] represents the maximum size of the square that can be formed
    // with (i, j) as the bottom-right cell of the would-be square.
    int maxSize = 0;
    vector<vector<int>> dp(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        // base-cases
        if (i == 0 || j == 0 || matrix[i][j] == '0') {
          // equivalent to 1 - 0 or 0 - 0
          dp[i][j] = matrix[i][j] - '0';
          maxSize = max(maxSize, dp[i][j]);
          continue;
        }

        // left, up, diagonal
        dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
        maxSize = max(maxSize, dp[i][j]);
      }
    }

    return maxSize * maxSize;
  }
};
