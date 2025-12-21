#include <string>
#include <vector>

class Solution {
 public:
  int minDeletionSize(std::vector<std::string>& strs) {
    // n strings of same length.
    // choose any indices, and delete all the characters in those indices for
    // each string.
    const auto n = static_cast<int>(strs.size());
    const auto m = static_cast<int>(strs[0].size());

    int result = 0;
    std::vector<bool> sorted(n - 1, false);
    for (int c = 0, r; c < m; ++c) {
      for (r = 0; r < n - 1; ++r) {
        if (!sorted[r] && strs[r][c] > strs[r + 1][c]) {
          ++result;
          break;
        }
      }
      if (r < n - 1) {
        continue;
      }

      for (r = 0; r < n - 1; ++r) {
        sorted[r] = sorted[r] || (strs[r][c] < strs[r + 1][c]);
      }
    }
    return result;
  }
};
