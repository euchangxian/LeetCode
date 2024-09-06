#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  vector<vector<int>> insert(vector<vector<int>> &intervals,
                             vector<int> &newInterval) {
    // intervals is already sorted in ascending order by start
    int n = intervals.size();
    vector<vector<int>> result;
    result.reserve(intervals.size() + 1);

    int i = 0;

    // Add all intervals that end before the start of newInterval
    while (i < n && intervals[i][1] < newInterval[0]) {
      result.push_back(intervals[i]);
      ++i;
    }

    // Merge overlapping intervals
    while (i < n && intervals[i][0] <= newInterval[1]) {
      newInterval[0] = min(newInterval[0], intervals[i][0]);
      newInterval[1] = max(newInterval[1], intervals[i][1]);
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
