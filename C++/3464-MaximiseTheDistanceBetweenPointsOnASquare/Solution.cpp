#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxDistance(int side, std::vector<std::vector<int>>& points, int k) {
    // side representing the edge length of a square with corners at:
    // (0, 0), (0, side), (side, 0), (side, side).
    // points[i] = [x, y] representing the coordinate of a point lying on the
    // boundary of the square.
    // Select k points such that the Minimum Manhattan Distance between any two
    // points is maximised.
    // Return the maximum possible minimum MD.
    //
    // - side <= 1E9
    // - 4 <= points.length <= min(4 * side, 15*10^3)
    // - 4 <= k <= min(25, points.length)
    //
    // N^3 solution is possible.
    // The maximum MD is obtained by points on opposite end of diagonals, then
    // opposite ends of the sides.
    // Try to pick points on opposite ends? Nope. Within each side, the MD
    // will be extremely small.
    // Given that we have to pick at least 4 points, pigeonhole principle
    // => points may be on the same side (if we need to pick > 4).
    //
    // Possibly: partition the points into their respective sides of the square:
    // 4 arrays.
    // Pick sequentially, determining the smallest MD.
    // Hm. Too naive.
    // We can binary search on the MD?
    // Hm. But how do we iterate each pass efficiently?
    // We only need to consider the points picked on the previous side,
    // and the points picked on the next side, when calculating MD.
    // Or rather, the closest point.
    //
    // For each side, pick a point, then try not to violate the target.
    // We can first pick the point that minimizes one variable part,
    // consistently.
    //
    // HMM. We can think of the coordinates on a straightline.
    // WLOG, clockwise order.
    // Up -> Right -> Down -> Left
    // Then it becomes greedily searching for the next coordinate with distance
    // >= target.
    // Don't need 4 sides, just two arrays, one sorted by ascending (x, y),
    // other sorted by descending (x, y).
    //
    // We can do better, by mapping the 2D points onto 1D coordinates.
    // (0, y) -> identity
    // (x, side) ->
    // (side, y) ->
    // ()
    const auto n = static_cast<int>(points.size());
    std::vector<long long> line;
    line.reserve(n);
    for (const auto& p : points) {
      auto x = p[0];
      auto y = p[1];
      if (x == 0) {
        line.emplace_back(y);
      } else if (y == side) {
        line.emplace_back(x + side);
      } else if (x == side) {
        line.emplace_back(side * 3LL - y);
      } else {
        line.emplace_back(side * 4LL - x);
      }
    }
    std::ranges::sort(line);

    auto feasible = [&](auto limit) {
      for (auto start : line) {
        auto end = start + side * 4LL - limit;
        auto curr = start;

        for (int i = 1; i < k; ++i) {
          auto it = std::ranges::lower_bound(line, curr + limit);
          if (it == line.end() || *it > end) {
            curr = -1;
            break;
          }
          curr = *it;
        }
        if (curr >= 0) {
          return true;
        }
      }
      return false;
    };

    auto left = 1LL;
    auto right = side;
    while (left < right) {
      auto mid = left + (right - left + 1) / 2;
      if (feasible(mid)) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    return left;
  }
};
