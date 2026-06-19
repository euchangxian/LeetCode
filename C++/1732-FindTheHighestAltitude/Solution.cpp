#include <algorithm>
#include <utility>
#include <vector>

class Solution {
 public:
  int largestAltitude(std::vector<int>& gain) {
    // n+1 points with different altitudes.
    // Start at point 0 with altitude 0.
    // gain[i] is the net gain between the i-th and (i+1)-th point.
    // Return the highest altitude.

    auto [_, result] = std::ranges::fold_left(
        gain, std::make_pair(0, 0), [](auto acc, auto x) {
          auto& [sum, result] = acc;
          result = std::max(result, sum += x);
          return acc;
        });
    return result;
  }
};
