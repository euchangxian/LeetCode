#include <algorithm>
#include <utility>
#include <vector>

using i64 = long long;

class Solution {
 public:
  i64 maxRunTime(int n, std::vector<int>& batteries) {
    // batteries[i]: ith battery can run a computer for batteries[i] minutes.
    // Want to run all n computers simultaneously.
    // Initially, insert at most one battery into each computer.
    // Afterwards, remove an insert another battery any number of times.
    // Return the maximum number of minutes all n computers can be run
    // simultaneously.
    //
    // Naive Greedy is not possible. Need to juggle batteries around.
    // If we have <= n batteries, then the maxRunTime is the minimum of the
    // batteries since we lack a "buffer" battery
    // Hm. We want to "greedily" minimise the difference between the minimum
    // and maximum battery.
    // BSTA
    // Seems like MaxFlow.
    auto feasible = [&](i64 target) {
      i64 extra = 0;
      for (i64 power : batteries) {
        // batteries[i] <= target => use all
        // batteries[i] > target => can only use target amount only
        extra += std::min(target, power);
      }
      return extra >= n * target;
    };

    auto [maxPower, totalPower] = [&]() {
      i64 maxPower = 0;
      i64 totalPower = 0;
      for (i64 power : batteries) {
        maxPower = std::max(maxPower, power);
        totalPower += power;
      }
      return std::make_pair(maxPower, totalPower);
    }();

    i64 left = 1;

    // get a tighter bound. (m-n+1) * maxPower
    i64 right =
        std::max(static_cast<int>(batteries.size()) - n + 1, 1) * maxPower;

    while (left < right) {
      auto mid = left + (right - left + 1LL) / 2LL;

      if (feasible(mid)) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    return left;
  }
};
