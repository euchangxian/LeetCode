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
  int minMeetingRooms(vector<Interval> &intervals) {
    sort(
        intervals.begin(), intervals.end(),
        [](Interval const &a, Interval const &b) { return a.start < b.start; });

    // Stores the earliest ending Meeting
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (Interval const &interval : intervals) {
      if (!minHeap.empty() && minHeap.top() <= interval.start) {
        minHeap.pop();
      }
      minHeap.push(interval.end);
    }

    return minHeap.size();
  }
};
