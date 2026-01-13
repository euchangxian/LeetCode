#include <algorithm>
#include <utility>
#include <vector>

constexpr auto EPSILON = 1E5;
class Solution {
 public:
  double separateSquares(std::vector<std::vector<int>>& squares) {
    // squares[i] = [x, y, l], coordinates of the bottom-left point, and the
    // side length.
    // Find the minimum y-coordinate value of a horizontal line such that the
    // total area of squares above the line is equal to above.
    //
    // Squares can overlap.
    // Sounds like a prefix area/sweep bottom-up
    const auto n = static_cast<int>(squares.size());
    std::vector<std::pair<int, int>> events;
    events.reserve(2 * n);

    double totalArea = 0;
    for (const auto& sq : squares) {
      int x = sq[0];
      int y = sq[1];
      int l = sq[2];

      totalArea += static_cast<double>(l) * l;
      events.emplace_back(y, l);
      events.emplace_back(y + l, -l);  // negative l => end of square.
    }

    std::ranges::sort(events);

    int width = 0;
    double currArea = 0;
    int prevHeight = 0;
    for (auto [y, l] : events) {
      auto heightDiff = y - prevHeight;
      auto areaDiff = static_cast<double>(width) * heightDiff;

      if (currArea + areaDiff >= totalArea / 2) {
        auto optimalHeightDiff = ((totalArea / 2) - currArea) / width;
        return prevHeight + optimalHeightDiff;
      }

      width += l;
      currArea += areaDiff;
      prevHeight = y;
    }
    std::unreachable();
  }
};
