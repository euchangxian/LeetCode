#include <array>
#include <vector>

class Solution {
 public:
  int numSpecial(std::vector<std::vector<int>>& mat) {
    // Given an mxn binary matrix, return the number of special positions in
    // mat.
    // A position (i, j) is special if mat[i][j] == 1, and all other elements
    // in row[i] and column[j] are 0.
    //
    // At most min(m, n) due to the implications.
    // Since we just need to count: we can count rowOnes[m] and colOnes[n]
    // indicating the number of 1s in each row/col.
    constexpr auto MAX_MN = 100;
    const auto m = static_cast<int>(mat.size());
    const auto n = static_cast<int>(mat[0].size());
    std::array<int, MAX_MN + 1> rowOnes{};
    std::array<int, MAX_MN + 1> colOnes{};
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (mat[r][c] == 1) {
          ++rowOnes[r];
          ++colOnes[c];
        }
      }
    }

    int result = 0;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (mat[r][c] == 1 && rowOnes[r] == 1 && colOnes[c] == 1) {
          ++result;
        }
      }
    }
    return result;
  }
};
