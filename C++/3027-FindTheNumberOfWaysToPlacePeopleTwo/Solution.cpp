#include <algorithm>
#include <functional>
#include <limits>
#include <vector>

class Solution {
 public:
  int numberOfPairs(std::vector<std::vector<int>>& points) {
    // points of size 2*n, where points[i] = (x, y)
    // Place n people, including Alice and Bob at these points such that
    // there is exactly one person at every point.
    // Alice wants to be alone with Bob, so Alice will build a rectangular fence
    // with Alice's position on the Upper Left Corner, and Bob's position as
    // the Lower Right Corner of the fence. No person should be inside or on
    // the fence.
    // Return the number of pairs of points possible.
    //
    // This is just obscured wording from the first variant, and a larger
    // constraint.
    // 2 <= n <= 1000
    const auto n = static_cast<int>(points.size());

    std::sort(points.begin(), points.end(), [](const auto& p1, const auto& p2) {
      if (p1[0] == p2[0]) {
        return std::greater<>{}(p1[1], p2[1]);
      }
      return std::less<>{}(p1[0], p2[0]);
    });

    int result = 0;
    for (int i = 0; i < n; ++i) {
      auto y1 = points[i][1];

      auto lastValidY = std::numeric_limits<int>::min();
      for (int j = i + 1; j < n; ++j) {
        auto y2 = points[j][1];

        if (y2 > y1) {
          continue;
        }

        if (y2 > lastValidY) {
          ++result;
          lastValidY = y2;
        }
      }
    }
    return result;
  }
};
