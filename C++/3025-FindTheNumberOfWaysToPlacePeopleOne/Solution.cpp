#include <algorithm>
#include <functional>
#include <vector>

class Solution {
 public:
  int numberOfPairs(std::vector<std::vector<int>>& points) {
    // 2D Plane, given points with size n*2, where points[i] = [x, y]
    // COunt the number of pairs of POINTS (P1, P2) where
    // - P1 is on the upper left side of P2, and
    // - there are no other points in the rectangle they make, including border.
    //
    // For the constraints:
    // n <= 50 => 2*n <= 100
    // seem to indicate an O(N^3) or even O(N^4) solution is viable.
    // Actually, why n*2? why not just give n points.
    //
    // E.g., For every pair of points, check if there are points enclosed.
    // Naturally, we can do better? Seems like we should sort the points to
    // avoid repetitive checks.
    // Then, if any points lie on the same horizontal/vertical line, they
    // will be excluded from any possible pairs.
    // It also creates a "gap" where points to their left cannot be paired with
    // points on the right?
    // Hm. Note that P1 must be on the upper-left.
    // As such, we can sort by ascending X, then descending Y.
    // Iterating over each point in ascending X, only consider points lower
    // than it, with a lower Y.
    // How can we determine if any points are enclosed?
    // E.g., A=(x1, y1), B=(x2, y2), no points C(x3, y3) such that:
    // x1 <= x3 <= x2 AND y1 <= y3 <= y2.
    auto ascendingXDescendingY = [](const auto& p1, const auto& p2) {
      if (p1[0] == p2[0]) {
        return std::greater{}(p1[1], p2[1]);
      }
      return std::less{}(p1[0], p2[0]);
    };

    int n = points.size();
    std::sort(points.begin(), points.end(), ascendingXDescendingY);

    int result = 0;
    for (int i = 0; i < n; ++i) {
      int x1 = points[i][0];
      int y1 = points[i][1];

      int y3 = -1;  // 0<=x,y<=50
      for (int j = i + 1; j < n; ++j) {
        int x2 = points[j][0];
        int y2 = points[j][1];
        // A must be on the top-left, exclude any points that lie higher than
        // A.
        if (y2 > y1) {
          continue;
        }

        // we already know x2 >= x1, so we keep-track of the y-coordinate of
        // the last seen valid rectangle.
        // If y2 <= lastSeenValidY, then that previous point found would be
        // enclosed within the current pair of points.
        if (y2 > y3) {
          ++result;
          y3 = y2;
        }
      }
    }
    return result;
  }
};
