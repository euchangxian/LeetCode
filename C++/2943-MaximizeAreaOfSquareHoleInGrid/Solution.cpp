#include <algorithm>
#include <span>
#include <vector>

class Solution {
 public:
  int maximizeSquareHoleArea(int n,
                             int m,
                             std::vector<int>& hBars,
                             std::vector<int>& vBars) {
    // Grid has n+2 horizontal, m+2 vertical bars, creating 1x1 unit cells.
    // 1-indexed.
    // Remove some bars in hBars/vBars.
    // Return an integer denoting the maximum area of a square-shaped hole
    // in the grid after removing >=0 bars.
    //
    // Basically, can only remove bars if they exist in hBars/vBars.
    // Want to remove as many consecutive bars to create a square.
    std::ranges::sort(hBars);
    std::ranges::sort(vBars);

    auto maxConsecutive = [](std::span<int> bars) {
      const auto n = static_cast<int>(bars.size());
      int result = 1;
      int curr = 1;
      for (int i = 1; i < n; ++i) {
        if (bars[i] - bars[i - 1] == 1) {
          ++curr;
        } else {
          curr = 1;
        }
        result = std::max(result, curr);
      }
      return result + 1;
    };

    auto len = std::min(maxConsecutive(hBars), maxConsecutive(vBars));
    return len * len;
  }
};
