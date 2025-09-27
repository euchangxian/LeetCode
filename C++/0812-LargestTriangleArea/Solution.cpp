#include <algorithm>
#include <cmath>
#include <vector>

class Solution {
 public:
  double largestTriangleArea(std::vector<std::vector<int>>& points) {
    // points[i] = [x, y], return the largest area that can be formed by any
    // three points.
    //
    // How to get area of a triangle given three points? Cosine rule?
    // NOTE: Area of trapezoids formed against the x-axis, simplified.
    // Area = 0.5 * |x1(y2-y3) + x2(y3-y1) + x3(y1-y2)|

    // Avoid 0.5x first.
    auto twoXArea = [](const auto& p1, const auto& p2, const auto& p3) {
      static constexpr std::size_t X = 0;
      static constexpr std::size_t Y = 1;

      return std::abs((p1[X] * (p2[Y] - p3[Y])) + (p2[X] * (p3[Y] - p1[Y])) +
                      (p3[X] * (p1[Y] - p2[Y])));
    };
    const auto n = static_cast<int>(points.size());

    int result = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        for (int k = j + 1; k < n; ++k) {
          result = std::max(result, twoXArea(points[i], points[j], points[k]));
        }
      }
    }
    return 0.5 * static_cast<double>(result);
  }
};
