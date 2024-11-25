#include <algorithm>
#include <vector>

class Solution {
 public:
  bool canAttendMeetings(std::vector<std::vector<int>>& intervals) {
    std::sort(intervals.begin(), intervals.end());

    // check for overlaps, i.e., if the previous meeting's ending cuts into the
    // current meeting.
    for (int i = 1; i < intervals.size(); ++i) {
      if (intervals[i - 1][1] > intervals[i][0]) {
        return false;
      }
    }
    return true;
  }
};
