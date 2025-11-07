#include <algorithm>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using i64 = long long;
class Solution {
 public:
  long long maxPower(std::vector<int>& stations, int r, int k) {
    // stations[i] represent the number of powers stations in the ith city.
    // Each station can provide power to every city in a fixed range r.
    // A power station at city[i] can provide power to every city[j] such that
    // |i-j| <= r.
    // The power of a city is the total number of power stations it is provided
    // power from.
    // k more power stations can be built in any city.
    // Return the maximum possible minimum power of a city.
    //
    // Hm.
    // Binary Search?
    // Obtain the initial state through a line sweep?
    // Then, for the feasibility check, upon encountering a city < limit at
    // index j, we add a city at city (j + r), such that cities (j+r) through
    // (j+2r) are powered by this newly added station.
    const auto n = static_cast<int>(stations.size());
    std::vector<i64> events(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      events[std::max(i - r, 0)] += stations[i];
      events[std::min(i + r + 1, n)] -= stations[i];
    }

    i64 minPower = std::numeric_limits<i64>::max();
    std::vector<i64> power(n);
    i64 prefix = 0;
    for (int i = 0; i < n; ++i) {
      prefix += events[i];
      power[i] = prefix;
      minPower = std::min(minPower, power[i]);
    }

    auto feasible = [&](i64 target) -> bool {
      // {idx, #stations}
      std::queue<std::pair<int, i64>> window;
      i64 used = 0;

      i64 addPower = 0;
      for (int i = 0; i < n; ++i) {
        while (!window.empty() && window.front().first < i) {
          addPower -= window.front().second;
          window.pop();
        }

        if (power[i] + addPower >= target) {
          continue;
        }

        i64 required = target - (power[i] + addPower);
        used += required;
        if (used > k) {
          return false;
        }
        addPower += required;

        auto expiryIdx = i + 2 * r;
        if (expiryIdx < n) {
          window.emplace(expiryIdx, required);
        }
      }

      return used <= k;
    };

    i64 left = minPower;
    i64 right = minPower + k;
    while (left < right) {
      i64 mid = left + (right - left + 1) / 2;

      if (feasible(mid)) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }

    return left;
  }
};
