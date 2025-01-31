#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<int> longestObstacleCourseAtEachPosition(
      std::vector<int>& obstacles) {
    // Similar to LIS/patience solitaire.
    // Except instead of strictly increasing, we do non-decreasing.
    // i.e., instead of
    // - appending trivially if x is greater than the back,
    // - replacing the first number of the LIS that is greater than or equal
    //   to x (std::lower_bound),
    //
    // we can relax the constraint by
    // - appending if greater than or equal to the back, or
    // - replacing the first number of the LIS that is strictly greater than
    //   x (std::upper_bound).

    // longest non-decreasing
    std::vector<int> lnds;
    lnds.reserve(obstacles.size());
    lnds.push_back(obstacles[0]);

    std::vector<int> answer(obstacles.size());
    answer[0] = 1;
    for (int i = 1; i < obstacles.size(); ++i) {
      if (obstacles[i] >= lnds.back()) {
        lnds.push_back(obstacles[i]);
        answer[i] = lnds.size();
      } else {
        auto it = std::upper_bound(lnds.begin(), lnds.end(), obstacles[i]);
        *it = obstacles[i];

        // must include this element.
        answer[i] = std::distance(lnds.begin(), it) + 1;
      }
    }
    return answer;
  }
};
