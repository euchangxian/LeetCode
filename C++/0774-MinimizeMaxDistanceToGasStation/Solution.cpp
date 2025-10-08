#include <algorithm>
#include <vector>

constexpr auto EPSILON = 1E-6;
class Solution {
 public:
  double minmaxGasDist(std::vector<int>& stations, int k) {
    // stations represent the positions of the gas stations on the x-axis.
    // Add k new gas stations on the x-axis, not necessarily on an integer
    // position.
    // The maximum distance between adjacent gas stations after adding k new
    // stations is penalty.
    // Return the smallest possible value of penalty.
    //
    // Hm. We always want to place a new station equidistant between two
    // stations.
    // i.e., (stations[j] - stations[i]) / x, where x is the number of stations
    // we place in between two stations.
    // Binary Search.
    const auto n = static_cast<int>(stations.size());

    auto feasible = [&](double maxDist) {
      int used = 0;
      for (int i = 1; i < n; ++i) {
        used += static_cast<int>((stations[i] - stations[i - 1]) / maxDist);
      }

      return used <= k;
    };

    double left = 0.0;
    double right = [&]() {
      int maxAdjDist = 0;
      for (int i = 1; i < n; ++i) {
        maxAdjDist = std::max(maxAdjDist, stations[i] - stations[i - 1]);
      }
      return maxAdjDist;
    }();

    while (right - left > EPSILON) {
      double mid = left + (right - left) / 2.0;
      if (feasible(mid)) {
        right = mid;
      } else {
        left = mid;
      }
    }
    return left;
  }
};
