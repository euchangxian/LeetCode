#include <algorithm>
#include <limits>
#include <unordered_set>
#include <utility>
#include <vector>

using i64 = long long;
class Solution {
 public:
  bool isReflected(std::vector<std::vector<int>>& points) {
    // Check if there is a line PARALLEL to the y-axis, that after reflecting
    // all points over the line, the original set of points is the same as the
    // reflected ones.
    // Collect the min-max x-coordinates.
    // Reflect the points, then check if the reflection exists.
    constexpr auto hash = [](const auto& p) {
      i64 x = p.first;
      i64 y = p.second;
      return (x << 32) | y;
    };

    std::unordered_set<std::pair<int, int>, decltype(hash)> seen;
    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    for (const auto& p : points) {
      minX = std::min(minX, p[0]);
      maxX = std::max(maxX, p[0]);
      seen.emplace(p[0], p[1]);
    }

    for (const auto& p : points) {
      // reflect p about the line.
      int rX = minX + maxX - p[0];
      std::pair<int, int> refP{rX, p[1]};
      if (!seen.contains(refP)) {
        return false;
      }
    }
    return true;
  }
};
