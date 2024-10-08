#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class MyCalendarThree {
 private:
  // Line sweep, {time, count}.
  std::map<int32_t, int32_t> calendar;

 public:
  MyCalendarThree() {}

  int book(int startTime, int endTime) {
    ++calendar[startTime];
    --calendar[endTime];

    int32_t prefix{0};
    int32_t k{0};
    for (const auto [time, count] : calendar) {
      prefix += count;
      k = std::max(k, prefix);
    }
    return k;
  }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */
