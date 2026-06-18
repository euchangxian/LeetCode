#include <algorithm>
#include <cmath>

class Solution {
 public:
  double angleClock(int hour, int minutes) {
    // return the smaller angle in degress formed between the hour and minute
    // hand.
    //
    // Wow.
    // Take one hand as the reference line, i.e., consider delta only.

    // delta from 0
    auto minuteDeg = static_cast<double>(minutes) / 60.0 * 360.0;
    auto hourDeg =
        (static_cast<double>(hour % 12) + static_cast<double>(minutes) / 60.0) /
        12.0 * 360.0;

    auto delta = std::fabs(hourDeg - minuteDeg);
    return std::min(delta, 360.0 - delta);
  }
};
