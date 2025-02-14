#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> merge(
      std::vector<std::vector<int>>& intervals) {
    int n = intervals.size();

    // Sort by start times in ascending order
    std::sort(intervals.begin(), intervals.end(),
              [](const auto& a, const auto& b) { return a[0] < b[0]; });

    std::vector<std::vector<int>> result;
    result.reserve(n);
    result.push_back(intervals[0]);

    for (int i = 1; i < n; ++i) {
      std::vector<int>& prev = result.back();

      // Merge overlaps
      if (intervals[i][0] <= prev[1]) {
        prev[1] = std::max(prev[1], intervals[i][1]);
      } else {
        result.push_back(intervals[i]);
      }
    }
    return result;
  }
};
