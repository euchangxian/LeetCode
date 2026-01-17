#include <algorithm>
#include <vector>

using i64 = long long;

class Solution {
 public:
  i64 largestSquareArea(std::vector<std::vector<int>>& bottomLeft,
                        std::vector<std::vector<int>>& topRight) {
    // n rectangles in a 2D plane with edges parallel to x and y-axis.
    // bottomLeft[i] = [a, b], topRight[i] = [c, d] representing the bottom left
    // and top right corners of the ith rectangle respectively.
    //
    // Project rectangles onto the x-axis.
    const auto n = static_cast<int>(bottomLeft.size());
    int side = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        auto overlapWidth = std::min(topRight[i][0], topRight[j][0]) -
                            std::max(bottomLeft[i][0], bottomLeft[j][0]);
        auto overlapHeight = std::min(topRight[i][1], topRight[j][1]) -
                             std::max(bottomLeft[i][1], bottomLeft[j][1]);
        side = std::max(side, std::min(overlapWidth, overlapHeight));
      }
    }

    return 1LL * side * side;
  }
};
