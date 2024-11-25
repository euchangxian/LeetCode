#include <algorithm>
#include <functional>
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
};
