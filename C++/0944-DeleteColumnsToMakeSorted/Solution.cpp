#include <string>
#include <vector>

class Solution {
public:
  int minDeletionSize(std::vector<std::string> &strs) {
    // given n strings, all of same length.
    // Arranged such that there is one string on each row, making a grid.
    // Delete the columns that are not sorted lexicographically.
    // Return the number of columns to delete.
    const auto n = static_cast<int>(strs.size());
    const auto m = static_cast<int>(strs[0].size());

    int result = 0;
    for (int c = 0; c < m; ++c) {
      for (int r = 1; r < n; ++r) {
        if (strs[r][c] < strs[r - 1][c]) {
          ++result;
          break;
        }
      }
    }
    return result;
  }
};
