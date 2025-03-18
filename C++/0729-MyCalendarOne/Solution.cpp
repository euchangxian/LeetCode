#include <set>

class MyCalendar {
 private:
  std::set<std::pair<int, int>> calendar;

 public:
  MyCalendar() {}

  // Return true if the event can be added to the calendar without causing a
  // double booking.
  // Event is represented as [start, end)
  bool book(int start, int end) {
    const std::pair<int, int> event{start, end};

    const auto nextEvent = calendar.lower_bound(event);
    if (nextEvent != calendar.end() && end > nextEvent->first) {
      return false;
    }

    // Check prev event if it exists
    if (nextEvent != calendar.begin()) {
      const auto prevEvent = prev(nextEvent);
      if (prevEvent->second > start) {
        return false;
      }
    }

    calendar.insert(event);
    return true;
  }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
