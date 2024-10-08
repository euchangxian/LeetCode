#include <algorithm>
#include <cstdint>
#include <queue>
#include <vector>

using namespace std;
class Solution {
 public:
  vector<int> minAvailableDuration(vector<vector<int>>& slots1,
                                   vector<vector<int>>& slots2,
                                   int duration) {
    // Notice that the problem constraints guarantee that the time slots of
    // the SAME person will not intersect. That means that if two time slots
    // intersect, they are guaranteed to be from different persons.
    //
    // Consequently, we can use a Heap to sort by start time. If we find two
    // timeslots that intersect, we know that they are from different persons,
    // and we can check the duration.
    //
    // To leverage further on this guarantee, we can choose to push intervals
    // that are at least of duration length. This allows us to guarantee that
    // if an interval is popped from the heap, there are only three possible
    // outcomes:
    // 1. The next interval is completely contained with the popped interval.
    //    In this case, we can return the answer
    // 2. The next interval has some overlaps, and ends later than the popped
    //    interval. In this case, we check if the overlapping duration satisfies
    //    what we are looking for. If satisfied, we can return the answer.
    //    Otherwise, the popped interval is no longer useful to use. This is
    //    because the next, next interval will either be from the same person,
    //    making it unceccessary to compare against, or the next next interval
    //    is from another person. The overlap between this interval and the
    //    popped interval will never increase, as the heap is ordered by start.
    // 3. The next interval has no overlap. Continue

    // Use a minHeap; smallest element are at the back of the container, and
    // will be popped first.
    std::priority_queue<vector<int>, vector<vector<int>>, greater<>> timeslots;
    for (const auto& interval : slots1) {
      if (interval[1] - interval[0] >= duration) {
        timeslots.push(interval);
      }
    }

    for (const auto& interval : slots2) {
      if (interval[1] - interval[0] >= duration) {
        timeslots.push(interval);
      }
    }

    while (timeslots.size() > 1) {
      auto interval1 = std::move(timeslots.top());
      timeslots.pop();

      const auto& interval2 = timeslots.top();

      if (interval1[1] >= interval2[0] + duration) {
        // Ordered by start time already, only need to check end time of the
        // popped interval overlaps.
        return {interval2[0], interval2[0] + duration};
      }
    }
    return {};
  }

  vector<int> minAvailableDurationNaive(vector<vector<int>>& slots1,
                                        vector<vector<int>>& slots2,
                                        int duration) {
    // Sort by start times. Traverse both arrays, if the slots are overlapping
    // and the overlapped portion is at least of duration, then that is our
    // answer.
    sort(slots1.begin(), slots1.end());
    sort(slots2.begin(), slots2.end());

    size_t i = 0;
    size_t j = 0;
    while (i < slots1.size() && j < slots2.size()) {
      const vector<int>& interval1 = slots1[i];
      const vector<int>& interval2 = slots2[j];

      const int32_t start = std::max(interval1[0], interval2[0]);
      const int32_t end = std::min(interval1[1], interval2[1]);

      if (end - start >= duration) {
        return {start, start + duration};
      }

      // Move the pointer of the interval that ends earlier. This is because
      // it won't be useful for finding a longer overlap
      if (interval1[1] < interval2[1]) {
        ++i;
      } else {
        ++j;
      }
    }
    return {};
  }
};
