#include <cmath>
#include <vector>

class Solution {
 public:
  long long minNumberOfSeconds(int mountainHeight,
                               std::vector<int>& workerTimes) {
    // workerHeight[i]: work time of ith worker in seconds.
    // Workers work simultaneously to reduce the height of the mountain.
    // To decrease the mountain height by x, it takes:
    //  workerTimes[i]+ (2*workerTimes[i]) + ... + (x*workerTimes[i])
    // E.g., workerTimes[i] * (1+2+...+x)
    // Return the minimum seconds to make height 0.
    //
    // Binary Search? Heap?
    // Using a worker increases the cost for the next reduction by k+1, where
    // k is the number of times the worker has been used already.
    // simultaneously... means to take the minimum...
    // Binary Search on the cost.
    using i64 = long long;

    auto feasible = [&](auto cost) {
      // workTime * x(x+1)/2 <= cost
      // x(x+1) <= (cost/workTime)*2
      // x^2 + x - 2C <= 0, C = cost/worktime
      // x = {-1 +- sqrt(1 + 8C)}/2 (quadratic formula, {-b +- sqrt(b^2-4ac))}/2
      i64 totalRemoved = 0;
      for (double t : workerTimes) {
        auto base = std::sqrt(1.0 + 8.0 * (cost / t));
        i64 x = (-1.0 + base) / 2.0;
        if (totalRemoved += x; totalRemoved >= mountainHeight) {
          return true;
        }
      }
      return false;
    };
    i64 left = 1;
    i64 right = 1E16;
    while (left < right) {
      auto mid = left + (right - left) / 2;
      if (feasible(mid)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};
