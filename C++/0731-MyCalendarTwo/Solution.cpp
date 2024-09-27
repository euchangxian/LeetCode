#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <climits>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Unlike CalendarOne, in CalendarTwo, we can add an event if it does not cause
 * a triple booking, i.e. when three events have some non-empty intersection.
 */
constexpr int kMaximumOverlap = 2;
class MyCalendarTwo {
private:
  // Map of {time: count}
  std::map<int, int> bookings;

public:
  MyCalendarTwo() {}

  bool book(int start, int end) {
    // Line Sweep. Find the prefix sum in between [start, end).
    // The prefix sum will indicate how many previous intervals started in
    // the interval [start, end).
    ++bookings[start];
    --bookings[end];

    int prefix{0};

    // Seemed a little counter-intuitive at first, where we iterate from the
    // start. But the prefixSum is incremented by start and decremented by the
    // end.
    for (const auto &[time, count] : bookings) {
      prefix += count;
      if (prefix > kMaximumOverlap) {
        --bookings[start];
        ++bookings[end];
        return false;
      }

      if (time >= end) {
        break;
      }
    }

    return true;
  }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
