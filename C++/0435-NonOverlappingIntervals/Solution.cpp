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
  int eraseOverlapIntervals(vector<vector<int>> &intervals) {
    int n = intervals.size();

    sort(intervals.begin(), intervals.end(), [](auto const &a, auto const &b) {
      // Sort by ascending start times
      return a[0] < b[0];
    });

    int result = 0;
    for (int i = 1; i < n; ++i) {
      if (intervals[i][0] < intervals[i - 1][1]) {
        ++result;
        // min to indicate remove
        intervals[i][1] = min(intervals[i][1], intervals[i - 1][1]);
      }
    }
    return result;
  }
};
