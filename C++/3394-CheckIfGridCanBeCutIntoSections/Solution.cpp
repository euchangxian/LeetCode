#include <algorithm>
#include <vector>

class Solution {
 public:
  bool checkValidCuts(int n, std::vector<std::vector<int>>& rectangles) {
    // n * n grid.
    // rectangle[i] = [start_x, start_y, end_x, end_y], where
    // (start_x, start_y) represent the bottom-left of the rectangle,
    // (end_x, end_y) represent the top-right.
    // Rectangles do not overlap.
    //
    // Determine if its possible to make two horizontal OR vertical cuts such
    // that:
    // - Each of the 3 resulting sections contain at least one rectangle
    // - Each rectangle belongs to exactly one section.
    //
    // Given the second constraint, probably sweep left-to-right, checking if
    // its possible to make vertical cuts,
    // then bottom-to-up to check for horizontal cuts.
    // Think there is a need to coalesce rectangles to avoid cutting rectangles,
    // i.e., merge intervals.
    // when sweeping left-to-right, consider (start_x, end_x).
    // when sweeping bottom-to-up, consider (start_y, end_y).
    // Given that n <= 10e9, naive line sweep is not optimal.
    //
    // Sort by ascending start, tie-broken by ascending end.
    // Look for two distinct non-overlaps, i.e., where we can cut.
    auto valid = [](const auto& intervals, int dim) {
      // Assume sorted by ascending start.
      int cuts = 0;
      int furthestEnd = intervals[0][dim + 2];
      for (int i = 1; i < intervals.size(); ++i) {
        int start = intervals[i][dim];
        int end = intervals[i][dim + 2];
        if (furthestEnd <= start) {
          ++cuts;
        }
        furthestEnd = std::max(furthestEnd, end);
      }
      return cuts >= 2;
    };

    // Left-To-Right
    std::ranges::sort(rectangles, {},
                      [](const auto& rec) -> int { return rec[0]; });
    if (valid(rectangles, 0)) {
      return true;
    }

    // Bottom-To-Up
    std::ranges::sort(rectangles, {},
                      [](const auto& rec) -> int { return rec[1]; });
    return valid(rectangles, 1);
  }
};
