#include <algorithm>
#include <vector>

class Solution {
 public:
  int countDays(int days, std::vector<std::vector<int>>& meetings) {
    // meetings[i] = [start, end] indicating starting and ending days of
    // the ith meeting (inclusive).
    // Sort by ascending start, tie-break by ascending end. sweep.
    // If prevEnd overlaps with currStart, then no free days.
    // Otherwise, += currStart - prevEnd.
    // Line Sweep is not better, since days <= 10e9
    std::sort(meetings.begin(), meetings.end());
    int available = meetings[0][0] - 1;
    int latestDay = meetings[0][1];
    for (int i = 1; i < meetings.size(); ++i) {
      available += std::max(0, meetings[i][0] - 1 - latestDay);
      latestDay = std::max(latestDay, meetings[i][1]);
    }
    return available + (days - latestDay);
  }
};
