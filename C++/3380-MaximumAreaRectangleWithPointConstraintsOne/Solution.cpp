#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class Solution {
 public:
  int maxRectangleArea(std::vector<std::vector<int>>& points) {
    // points[i] = [x, y] representing coordinates of a point on an INFINITE
    // 2D plane.
    //
    // Given small constraints, we can do an O(n^4) iteration over all possible
    // rectangles to determine the largest rectangle.
    // Ok, a bit more smartly, if (x1, y1) and (x2, y2) are two opposite corners
    // of a rectangle, i.e., top-left, bottom-right or top-right, bottom-left,
    // then (x1, y2) and (x2, y1) must be the other two points.
    const int n = points.size();
    int largestArea = -1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (j == i) {
          continue;
        }
      }
    }
  }
};
