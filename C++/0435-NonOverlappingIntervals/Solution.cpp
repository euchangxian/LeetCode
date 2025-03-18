#include <algorithm>
#include <vector>

class Solution {
 public:
  int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
    int n = intervals.size();

    sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
      // Sort by ascending start times
      return a[0] < b[0];
    });

    int result = 0;
    for (int i = 1; i < n; ++i) {
      if (intervals[i][0] < intervals[i - 1][1]) {
        ++result;
        // min to indicate remove
        intervals[i][1] = std::min(intervals[i][1], intervals[i - 1][1]);
      }
    }
    return result;
  }
};
