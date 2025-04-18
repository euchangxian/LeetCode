#include <algorithm>
#include <deque>
#include <utility>
#include <vector>

using i64 = long long;

class Solution {
 public:
  int maximumRobots(std::vector<int>& chargeTimes,
                    std::vector<int>& runningCosts,
                    i64 budget) {
    // Sliding window-like.
    // Maintain max with a monotonic non-increasing deque.
    // Then, if cost <= budget, expand right.
    // Otherwise, shrink left.
    const int n = chargeTimes.size();

    int best = 0;
    // {index, val}.
    std::deque<std::pair<int, int>> windowMax;
    i64 windowSum = 0;
    int l = 0;
    for (int r = 0; r < n; ++r) {
      while (!windowMax.empty() && windowMax.back().second <= chargeTimes[r]) {
        windowMax.pop_back();
      }

      windowMax.emplace_back(r, chargeTimes[r]);
      windowSum += runningCosts[r];
      while (true) {
        int max = windowMax.empty() ? 0 : windowMax.front().second;
        i64 cost = max + (r - l + 1) * windowSum;

        if (cost <= budget) {
          break;
        }

        windowSum -= runningCosts[l];
        if (windowMax.front().first == l) {
          // not necessary to check for non-empty. Else the cost would have
          // been 0.
          windowMax.pop_front();
        }
        ++l;
      }
      best = std::max(best, r - l + 1);
    }
    return best;
  }
};
