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
class Interval {
 public:
  int start, end;
  Interval(int start, int end) : start(start), end(end) {}
};

using namespace std;
class Solution {
 public:
  bool canAttendMeetings(vector<Interval>& intervals) {
    sort(
        intervals.begin(), intervals.end(),
        [](Interval const& a, Interval const& b) { return a.start < b.start; });

    for (int i = 1; i < intervals.size(); ++i) {
      if (intervals[i].start < intervals[i - 1].end) {
        return false;
      }
    }
    return true;
  }
};
