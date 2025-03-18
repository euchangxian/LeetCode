#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals,
                                       std::vector<int>& newInterval) {
    // intervals is already sorted in ascending order by start
    int n = intervals.size();
    std::vector<std::vector<int>> result;
    result.reserve(intervals.size() + 1);

    int i = 0;

    // Add all intervals that end before the start of newInterval
    while (i < n && intervals[i][1] < newInterval[0]) {
      result.push_back(intervals[i]);
      ++i;
    }

    // Merge overlapping intervals
    while (i < n && intervals[i][0] <= newInterval[1]) {
      newInterval[0] = std::min(newInterval[0], intervals[i][0]);
      newInterval[1] = std::max(newInterval[1], intervals[i][1]);
      ++i;
    }
    result.push_back(newInterval);

    // Add all non-overlapping intervals that start after the end of newInterval
    while (i < n) {
      result.push_back(intervals[i]);
      ++i;
    }

    return result;
  }
};
