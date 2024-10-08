#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 private:
 public:
  int findMinDifference(vector<string>& timePoints) {
    size_t const n = timePoints.size();
    vector<int> minutes(n, 0);
    for (int i = 0; i < n; ++i) {
      int h = stoi(timePoints[i].substr(0, 2));
      int m = stoi(timePoints[i].substr(3, 2));

      minutes[i] = h * 60 + m;
    }

    sort(minutes.begin(), minutes.end());

    // Check wrap-around
    // Done by checking the number of minutes from the largest minutes to 00:00
    // Then taking the first point after 00:00
    // E.g. 23:59 = 1439 minutes => 1 minute to 00:00 + 00:05 = 5minutes
    int minDiff = (24 * 60 - minutes[n - 1]) + minutes[0];

    for (int i = 1; i < n; ++i) {
      int diff = minutes[i] - minutes[i - 1];
      minDiff = min(minDiff, diff);
    }

    return minDiff;
  }
};
