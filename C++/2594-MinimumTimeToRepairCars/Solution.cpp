#include <algorithm>
#include <cmath>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 repairCars(std::vector<int>& ranks, int cars) {
    // rank[i] can repair n cars in r*n^2 minutes.
    // Minimum time to repair all cars.
    // All can repair simultaneously.
    // Hm. Not easy to determine the optimal choices i.e., which engineer
    // should repair, and how many cars they should repair.
    // BSTA.
    const int n = ranks.size();
    auto feasible = [&ranks, cars](i64 time) -> bool {
      i64 repaired = 0;
      for (int rank : ranks) {
        i64 nSqred = time / rank;
        repaired += std::floor(std::sqrt(nSqred));
      }
      return repaired >= cars;
    };

    auto min = std::min_element(ranks.begin(), ranks.end());
    i64 left = *min;
    i64 right = static_cast<i64>(*min) * cars * cars;

    while (left < right) {
      i64 mid = left + (right - left) / 2;
      if (feasible(mid)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};
