#include <bitset>
#include <vector>

class Solution {
 public:
  bool findRotation(std::vector<std::vector<int>>& mat,
                    std::vector<std::vector<int>>& target) {
    // given n*n binary matrices, return true if it is possible to make
    // mat equal to target by rotating mat in 90-degree increments, or false
    // otherwise.
    //
    // Must we actually simulate?
    // Can check row-by-row, without actually rotating.
    // 0-degree: row equality
    // 90-degree: first row of mat -> last column of target
    // 180-degree: first row of mat -> last row of target, reversed.
    // 270-degree: first row of mat -> first column of target, reversed.
    const auto n = static_cast<int>(mat.size());
    std::bitset<4> equal;
    equal.set();

    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        equal[0] = equal[0] & (mat[r][c] == target[r][c]);
        equal[1] = equal[1] & (mat[r][c] == target[c][n - 1 - r]);
        equal[2] = equal[2] & (mat[r][c] == target[n - 1 - r][n - 1 - c]);
        equal[3] = equal[3] & (mat[r][c] == target[n - 1 - c][r]);
      }
    }
    return equal.any();
  }
};
