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
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using i64 = long long;
constexpr int MOD = 1'000'000'007;
class Solution {
 public:
  int rectangleArea(std::vector<std::vector<int>>& rectangles) {
    // Line Sweep?
    // rectangles[i] = {x1, y1, x2, y2}, where (x1, y1) indicate the coordinates
    // of the bottom-left corner, while (x2, y2) indicate the top-right.
    // A little processing such that x1, x2 become events, with y2 as the
    // height.
    // Then, the problem is reduced to a more doable Line Sweep.
    //
    // To handle overlapping areas/rectangles, a Set is used as a PQ ADT, so
    // that the maximum height at a point can be retrieved efficiently.
    // When an end-event is reached, determine the area of the rectangle formed
    // by taking (currX - prevX) * height
    //
    // Ah. The bottom-left corner does not necessarily have y=0. Wrong
    // assumption.
    // In this manner, we may have disjoint rectangles, one above the other.
    // Naively taking the max height would then overcount the area.
    // Feels like a Range Query of some sorts.

    // inclusive ends, handle end event first.
    // Tie-break necessary?
    // {x, height}
    // negative heights indicate end events
    std::vector<std::pair<i64, i64>> events;
    events.reserve(rectangles.size() * 2);
    for (const auto& rectangle : rectangles) {
      // while the constraints are 0 <= ... y2 <= 10e9
      // another constraint mentions non-zero area. Therefore, height should
      // not be 0, and there is no need to handle it.
      i64 x1 = rectangle[0], x2 = rectangle[2], y2 = rectangle[3];
      events.emplace_back(x1, y2);
      events.emplace_back(x2, -y2);
    }
    std::sort(events.begin(), events.end());

    i64 area = 0;

    // Use first event which must be a Start event to simplify handling of prevX
    // Include a sentinel 0 to also simplify checking of maxHeight
    std::multiset<i64> heights{0, events[0].second};
    i64 prevX = events[0].first;
    for (const auto [x, height] : events) {
      // Calculate area up to current x
      i64 currHeight = *heights.rbegin();  // Get current max height
      area = (area + (currHeight * (x - prevX)) % MOD) % MOD;

      if (height > 0) {
        heights.insert(height);
      } else {
        heights.extract(-height);
      }

      prevX = x;
    }
    return area;
  }
};
