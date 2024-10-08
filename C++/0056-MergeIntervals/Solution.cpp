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
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    int n = intervals.size();

    // Sort by start times in ascending order
    sort(intervals.begin(), intervals.end(),
         [](auto const& a, auto const& b) { return a[0] < b[0]; });

    vector<vector<int>> result;
    result.reserve(n);
    result.push_back(intervals[0]);

    for (int i = 1; i < n; ++i) {
      vector<int>& prev = result.back();

      // Merge overlaps
      if (intervals[i][0] <= prev[1]) {
        prev[1] = max(prev[1], intervals[i][1]);
      } else {
        result.push_back(intervals[i]);
      }
    }
    return result;
  }
};
