#include <algorithm>
#include <array>
#include <utility>
#include <vector>

constexpr int MAX_N = 200;

class Solution {
 public:
  int minimumTotal(std::vector<std::vector<int>>& triangle) {
    const auto n = static_cast<int>(triangle.size());

    std::array<int, MAX_N + 1> dp;
    std::memcpy(dp.data(), triangle.back().data(),
                triangle.back().size() * sizeof(int));

    for (int r = n - 2; r >= 0; --r) {
      const auto& row = triangle[r];
      for (int i = 0; i <= r; ++i) {
        dp[i] = std::min(dp[i], dp[i + 1]) + row[i];
      }
    }
    return dp[0];
  }

  int minimumTotalBottomUp(std::vector<std::vector<int>>& triangle) {
    // from index i of the current row, move to i or i+1 on the next row.
    // In other words, from index i of the next row, come from i or i-1
    const auto n = static_cast<int>(triangle.size());

    std::array<int, MAX_N + 1> dp{};
    dp[0] = triangle[0][0];
    for (int r = 1; r < n; ++r) {
      const auto& row = triangle[r];
      std::array<int, MAX_N + 1> curr{};

      // both ends have only one choice
      curr[0] = dp[0] + row[0];
      curr[r] = dp[r - 1] + row[r];

      // r+1 is the number of cells in the current row
      for (int i = 1; i < r; ++i) {
        curr[i] = std::min(dp[i - 1], dp[i]) + row[i];
      }
      dp = std::move(curr);
    }
    return *std::min_element(dp.begin(), dp.begin() + n);
  }
};
