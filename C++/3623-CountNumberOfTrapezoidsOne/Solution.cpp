#include <unordered_map>
#include <vector>

using i64 = long long;

constexpr int MOD = 1E9 + 7;

class Solution {
 public:
  int countTrapezoids(std::vector<std::vector<int>>& points) {
    // points[i] = [x, y], coordinates of the ith point on the Cartesian Plane.
    // A horizontal trapezoid is a convex quadrilateral with at least one pair
    // of horizontal sides (parallel to the x-axis).
    // Return the number of unique horizontal trapezoids that can be formed
    // by choosing any four distinct points from points modulo 1E9+7.
    //
    // Brute force will not work considering points.length <= 1E5.
    // Suppose we have all the "lines" parallel to the x-axis (each of which
    // is 2 points), then we can combine them.
    // Therefore, we want to "group" points by their y-coordinates.
    // Points with the same y-coordinates create lines that are parallel to
    // the x-axis, and can be combined with lines with a different
    // y-coordinates.

    std::unordered_map<int, int> freq;
    for (const auto& point : points) {
      auto y = point[1];
      ++freq[y];  // points are pairwise distinct, we do not need to track x.
    }

    i64 result = 0;
    i64 prefix = 0;
    for (auto [_, count] : freq) {
      auto lines = count * (count - 1LL) / 2LL;

      result = (result + (lines * prefix)) % MOD;
      prefix += lines;
    }
    return result;
  }
};
