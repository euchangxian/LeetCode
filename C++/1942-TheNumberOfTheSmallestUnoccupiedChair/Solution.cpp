#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

class Solution {
 public:
  int smallestChair(std::vector<std::vector<int>>& times, int targetFriend) {
    // n friends from [0..n-1] attending.
    // infinite chairs.
    // times[i] represent {arrivalTime, departureTime} of friend i
    // Not sorted.
    const std::size_t n = times.size();

    // Instead of having an entire array of indices, just store the
    // targetArrivalTime. The question guarantees unique arrivalTimes.
    const int targetArrivalTime = times[targetFriend][0];

    // Allows efficient lookup of the minimum numbered chair available.
    std::priority_queue<int, std::vector<int>, std::greater<int>>
        availableChairs;
    for (int i = 0; i < n; ++i) {
      availableChairs.push(i);
    }

    std::sort(times.begin(), times.end());

    // {time, chairIdx}
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<>>
        departureQueue;

    // Determine when to reclaim chairs.
    for (const auto& time : times) {
      const int currTime = time[0];

      // Reclaim chairs first
      while (!departureQueue.empty() &&
             departureQueue.top().first <= currTime) {
        const int reclaimIdx = departureQueue.top().second;
        departureQueue.pop();
        availableChairs.push(reclaimIdx);
      }

      // Unless input is wrong, there will always be an available chair.
      // No need to check for empty
      const int chairIdx = availableChairs.top();
      availableChairs.pop();

      if (currTime == targetArrivalTime) {
        return chairIdx;
      }

      const int departureTime = time[1];
      departureQueue.emplace(departureTime, chairIdx);
    }

    return -1;
  }
};
