#include <algorithm>
#include <limits>
#include <vector>

class Solution {
 public:
  int minimumArea(std::vector<std::vector<int>>& grid) {
    // Given a 2D binary matrix.
    // Find a rectangle with the smallest area that covers all the 1s.
    //
    // Simple.
    // L: Column of leftmost 1,
    // R: Column of rightmost 1,
    // T: Row of topmost 1,
    // B: bottommost 1.
    // Area = (R-L+1) * (B-T+1)
    const auto rows = grid.size();
    const auto cols = grid[0].size();

    int left = std::numeric_limits<int>::max();
    int right = std::numeric_limits<int>::min();

    int top = std::numeric_limits<int>::max();
    int bottom = std::numeric_limits<int>::min();
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        if (grid[r][c] != 1) {
          continue;
        }

        left = std::min(left, c);
        right = std::max(right, c);

        top = std::min(top, r);
        bottom = std::max(bottom, r);
      }
    }

    return (right - left + 1) * (bottom - top + 1);
  }
};
