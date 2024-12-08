#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maxTwoEvents(std::vector<std::vector<int>>& events) {
    // Does Greedy work? Sort by value, then stable sort by start time.
    // Nope. Consider the super simple case:
    // {1, 4, 10}, {2, 3, 100}.
    // The algorithm would pick the interval {1, 4} first.
    // i.e., intervals contained within another interval may be wrongly skipepd.
    //
    // Thus we need a more sophisticated approach. First glance seems like
    // Line Sweep.
    // Visualizing the intervals as points on the x-axis, the y-axis would be
    // the value.
    // How can we determine the maximum sum of two non-overlapping events
    // though?
    // A little bit of visualization here is needed too. Once an event has
    // ended, it is guaranteed that in the iteration, any subsequent event will
    // not be overlapping with this event (to handle inclusive end, add one to
    // the end time in the preprocessing step.)
    // Thus, we can try to combine subsequent event with previously ended
    // events.

    // {time, isStart, value}
    // WARNING: for events occuring at the same time, e.g., startEvent,
    // endEvent, isStart will be used as the tiebreaker. This is because we
    // want to prioritise handling events that ended, so that we can get the
    // possibly new `prevMax` value.
    std::vector<std::array<int, 3>> line;
    line.reserve(events.size() * 2);
    for (const auto& event : events) {
      int start = event[0];
      int end = event[1];
      int value = event[2];

      line.push_back({start, true, value});
      line.push_back({end + 1, false, value});
    }
    std::sort(line.begin(), line.end());

    int maxSum = 0;
    int prevMax = 0;
    for (const auto [time, isStart, value] : line) {
      if (isStart) {
        maxSum = std::max(maxSum, prevMax + value);
      } else {
        prevMax = std::max(prevMax, value);
      }
    }

    return maxSum;
  }
};
