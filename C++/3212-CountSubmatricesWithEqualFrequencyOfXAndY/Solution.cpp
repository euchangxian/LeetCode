#include <array>
#include <bitset>
#include <vector>

constexpr auto MAX_MN = 1000;
class Solution {
 public:
  int numberOfSubmatrices(std::vector<std::vector<char>>& grid) {
    // Given 2D grid, grid[i][j] = 'X'|'Y'|'.'.
    // Return the number of submatrices that contain:
    // - grid[0][0]
    // - equal frequency of 'X', 'Y'
    // - at least one 'X'
    //
    // Prefix frequencies.
    // Once a column has an 'X', we can mark it as valid.
    // The rest, we can keep track using +1 for X, -1 for Y.
    constexpr auto signum = [](char c) {
      if (c == 'X') {
        return 1;
      }
      if (c == 'Y') {
        return -1;
      }
      return 0;
    };

    const auto m = static_cast<int>(grid.size());
    const auto n = static_cast<int>(grid[0].size());
    std::array<int, MAX_MN + 1> colSum{};
    std::bitset<MAX_MN + 1> colHasX{};

    auto result = 0;
    for (const auto& row : grid) {
      auto submatrixSum = 0;
      bool submatrixX = false;
      for (int c = 0; c < n; ++c) {
        colSum[c] += signum(row[c]);
        colHasX[c] = colHasX[c] | (row[c] == 'X');

        submatrixSum += colSum[c];
        submatrixX |= colHasX[c];

        result += (submatrixSum == 0 && submatrixX);
      }
    }
    return result;
  }
};
