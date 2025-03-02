#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

#ifdef LOCAL
class Interval {
 public:
  int start;
  int end;
  Interval(int start, int end) : start(start), end(end) {}
};
#endif  // LOCAL

class Solution {
 public:
  std::vector<Interval> employeeFreeTime(
      std::vector<std::vector<Interval>> schedule) {
    // schedule[i] represents the list of working time, sorted in ascending
    // order of the ith employee.
    //
    // Return the list of intervals representing the COMMON, FINITE,
    // POSITIVE-LENGTH, FREE time that ALL employees have.
    // ^ all keywords. Lol.
    //
    // Note the constraint schedule[i].start/end <= 10^8, effectively ruling
    // out naive Range Data Structures.
    //
    // Line Sweep? Maintain a prefix of FREE employees, k.
    // When k == n, then the condition is met and this interval is valid.
    // When k < n, then the condition is not met. End the existing interval,
    // Start a new one when the condition is met again.
    // Overall, core approach seems simple, implementation, not so.
    const int n = schedule.size();

    // {time, isEnd}
    // order start events earlier.
    std::vector<std::pair<int, bool>> events;
    events.reserve(50 * 50);  // schedule.length,schedule[i].length <= 50
    for (const auto& sched : schedule) {
      for (const auto [start, end] : sched) {
        events.emplace_back(start, false);
        events.emplace_back(end, true);
      }
    }
    std::sort(events.begin(), events.end());

    std::vector<Interval> result;
    result.reserve(50 * 50);

    int start = INT_MIN;
    int k = n;
    for (const auto [time, isEnd] : events) {
      if (!isEnd) {
        --k;
      } else {
        ++k;
      }

      // end of current free interval.
      if (k < n && start != INT_MIN) {
        result.emplace_back(start, time);
        start = INT_MIN;  // reset this.
      }

      if (k == n) {
        start = time;
      }
    }

    return result;
  }
};
