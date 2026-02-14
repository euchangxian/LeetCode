#include <vector>

class Solution {
 public:
  double champagneTower(int poured, int query_row, int query_glass) {
    // Pyramid
    // First row has 1 glass, second row has 2, ...
    // When top glass is full, excess will fall equally to left and right.
    //
    // Return how much champagne is in (query_row,query_glass)
    std::vector<double> dp(query_row + 2, 0);
    dp[0] = poured;
    for (int i = 1; i <= query_row; ++i) {
      for (int j = i; j >= 0; --j) {
        dp[j] = std::max((dp[j] - 1) / 2, 0.0);
        dp[j + 1] += dp[j];
      }
    }
    return std::min(dp[query_glass], 1.0);
  }
};
