#include <algorithm>
#include <ranges>
#include <vector>

class Solution {
 public:
  int removeCoveredIntervals(std::vector<std::vector<int>>& intervals) {
    enum Idx : std::size_t {
      Left,
      Right,
    };

    // intervals[i] = [l, r] representing the interval [l, r).
    // Remove all intervals that are covered by another interval in the list.
    // [a, b) is covered by [c, d) iff c <= a and b <= d.
    //
    // c..a..b..d
    // Greedy.
    // Sort by start-ascending, tie-break by end-descending
    // If prev.left <= curr.left && curr.right <= prev.right then that interval
    // is covered, and we can remove it.
    const auto n = static_cast<int>(intervals.size());

    std::sort(intervals.begin(), intervals.end(),
              [](const auto& i1, const auto& i2) {
                if (i1[Idx::Left] == i2[Idx::Left]) {
                  return i1[Idx::Right] > i2[Idx::Right];
                }
                return i1[Idx::Left] < i2[Idx::Left];
              });

    auto& prev = intervals.front();
    auto result = 1;
    for (const auto& curr : intervals | std::views::drop(1)) {
      if (prev[Idx::Left] <= curr[Idx::Left] &&
          curr[Idx::Right] <= prev[Idx::Right]) {
        continue;
      }
      ++result;
      prev = curr;
    }
    return result;
  }
};
