#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

constexpr std::array<std::array<int, 2>, 4> directions{{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};

class Solution {
 public:
  int longestIncreasingPath(std::vector<std::vector<int>>& matrix) {
    // Longest increasing path is just itself at the start.
    const std::size_t rows{matrix.size()};
    const std::size_t cols{matrix[0].size()};
    std::vector<std::vector<int>> memo(rows, std::vector<int>(cols, 1));
    int32_t result{1};
    for (std::size_t i{0}; i < rows; ++i) {
      for (std::size_t j{0}; j < cols; ++j) {
        result = std::max(result, dfs(matrix, memo, i, j));
      }
    }
    return result;
  }

 private:
  int dfs(const std::vector<std::vector<int>>& matrix,
          std::vector<std::vector<int>>& memo,
          size_t r,
          size_t c) {
    if (memo[r][c] > 1) {
      return memo[r][c];
    }

    for (const auto& [dr, dc] : directions) {
      const int32_t nr = r + dr;
      const int32_t nc = c + dc;

      if (nr < 0 || nr >= matrix.size() || nc < 0 || nc >= matrix[0].size()) {
        continue;
      }

      if (matrix[nr][nc] > matrix[r][c]) {
        memo[r][c] = std::max(memo[r][c], dfs(matrix, memo, nr, nc) + 1);
      }
    }
    return memo[r][c];
  }
};
