#include <algorithm>
#include <cmath>
#include <vector>

class Solution {
 public:
  int minTimeToVisitAllPoints(std::vector<std::vector<int>>& points) {
    // n points.
    // points[i] = [x, y]
    // Return the minimum time in seconds to visit all points in the order given
    // by points.
    // In 1 saecond, move either vertically/horizontally/diagonally by 1 unit.
    //
    // Greedy.
    // Optimally: diagonal(min{x, y}) + remaining(x or y)
    // We can simplify this:
    // diagonal = std::min(dx, dy)
    // remaining = std::max(dx, dy) - diagonal
    // time = diagonal + remaining = remaining.
    const auto n = static_cast<int>(points.size());
    int result = 0;
    for (int i = 1; i < n; ++i) {
      auto dx = std::abs(points[i][0] - points[i - 1][0]);
      auto dy = std::abs(points[i][1] - points[i - 1][1]);
      result += std::max(dx, dy);
    }
    return result;
  }
};
