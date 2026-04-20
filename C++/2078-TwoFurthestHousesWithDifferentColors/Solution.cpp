#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxDistance(std::vector<int>& colors) {
    // N evenly spaced houses painted.
    // colors[i] represent the color of the i-th house.
    // Return the maximum distance between two houses with different colours.
    //
    // - colors[i] <= 100
    constexpr int MAX_N = 100;
    const auto n = static_cast<int>(colors.size());

    int result = 0;

    // Compare everything against the first house
    for (int i = n - 1; i >= 0; --i) {
      if (colors[i] != colors[0]) {
        result = std::max(result, i);  // distance is i - 0
        break;
      }
    }

    // Compare everything against the last house
    for (int i = 0; i < n; ++i) {
      if (colors[i] != colors[n - 1]) {
        result = std::max(result, (n - 1) - i);
        break;
      }
    }

    return result;
  }
};
