#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <set>
#include <tuple>
#include <vector>

class Solution {
 public:
  std::vector<int> amountPainted(std::vector<std::vector<int>>& paint) {
    // Hm. Given that paint[i] is not sorted in ascending order, not trivial to
    // determine the amount of new area.
    // Need to be able to keep track of the original index, i.e., the day
    // that this interval was painted, as well as keep track of overlapping
    // intervals, i.e., painted on earlier days.
    // Line Sweep / Events processing?
    // At each event, keep track of the original day. Process in sorted order
    // the leftmost x-coordinate, tie-broken by the day it was painted
    // (prefer earlier).
    // Also, maintain a results array where result[i] = new area painted
    // When processing a start event, increment the prefix. If prefix > 1,
    // then the area between this start and (possibly multiple) end events
    // will not be counted.
    //
    // Hmmm. Observe that we kinda need a minStack/heap kinda data structure,
    // where until the interval (of an earlier day) ends, the next day will
    // not be used.
    // This ADT informs us which day the painted region should belong to.
    //
    // So, something like:
    // - start => add to ADT
    // - end => pop from ADT
    // - both: add area to result[i].
    //   Hm, maintain a prevX variable.
    // okay, lets try running through.
    // {1, 4}, {4, 7}, {5, 8}
    // events =
    //   {{1,start,0},{4,end,0},{4,start,1},{5,start,2},{7,end,1},{8,end,2}}
    // seems fine to me.

    // {x, isStart, idx/day}
    // Assign 1 to start events, 0 to end, so that End events will be
    // processed first.
    std::vector<std::tuple<int, bool, int>> events;
    events.reserve(paint.size() * 2);
    for (int i = 0; i < paint.size(); ++i) {
      events.emplace_back(paint[i][0], true, i);
      events.emplace_back(paint[i][1], false, i);
    }
    std::sort(events.begin(), events.end());

    std::vector<int> worklog(paint.size(), 0);
    std::set<int> currentDay;  // Set for random erase.
    int prevX = -1;
    for (const auto [x, isStart, day] : events) {
      if (!currentDay.empty()) {
        int idx = *currentDay.begin();
        worklog[idx] += x - prevX;
      }

      if (isStart) {
        currentDay.insert(day);
      } else {
        currentDay.erase(day);
      }

      prevX = x;
    }

    return worklog;
  }
};
