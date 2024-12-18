#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <vector>

class Solution {
 public:
  int minMeetingRooms(std::vector<std::vector<int>>& intervals) {
    std::sort(intervals.begin(), intervals.end());

    // Stores the earliest ending Meeting
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    for (const auto& interval : intervals) {
      if (!minHeap.empty() && minHeap.top() <= interval[0]) {
        minHeap.pop();
      }
      minHeap.push(interval[1]);
    }

    return minHeap.size();
  }

  int minMeetingRoomsSweep(std::vector<std::vector<int>>& intervals) {
    // line sweep version: find the maximum number of intersections between
    // points.
    std::map<int, int> events;
    for (const auto& interval : intervals) {
      const int start = interval[0];
      const int incEnd = interval[1];

      ++events[start];
      --events[incEnd];
    }

    int maxSum = 0;
    int sum = 0;
    for (const auto [time, count] : events) {
      sum += count;
      maxSum = std::max(maxSum, sum);
    }
    return maxSum;
  }
};
