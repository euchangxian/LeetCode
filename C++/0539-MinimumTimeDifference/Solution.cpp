#include <algorithm>
#include <string>
#include <vector>

class Solution {
 private:
 public:
  int findMinDifference(std::vector<std::string>& timePoints) {
    const std::size_t n = timePoints.size();
    std::vector<int> minutes(n, 0);
    for (int i = 0; i < n; ++i) {
      int h = std::stoi(timePoints[i].substr(0, 2));
      int m = std::stoi(timePoints[i].substr(3, 2));

      minutes[i] = h * 60 + m;
    }

    std::sort(minutes.begin(), minutes.end());

    // Check wrap-around
    // Done by checking the number of minutes from the largest minutes to 00:00
    // Then taking the first point after 00:00
    // E.g. 23:59 = 1439 minutes => 1 minute to 00:00 + 00:05 = 5minutes
    int minDiff = (24 * 60 - minutes[n - 1]) + minutes[0];

    for (int i = 1; i < n; ++i) {
      int diff = minutes[i] - minutes[i - 1];
      minDiff = std::min(minDiff, diff);
    }

    return minDiff;
  }
};
