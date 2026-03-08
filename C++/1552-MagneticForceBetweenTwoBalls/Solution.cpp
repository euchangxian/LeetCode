#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxDistance(std::vector<int>& position, int m) {
    // n empty baskets, ith basket is at position[i].
    // m balls, distribute such that the minimum magnetic force between any two
    // balls are at the maximum.
    // magnetic force between two different balls at position x and y is |x-y|.
    //
    // i.e., try to place the balls such that the minimum distance between any
    // two balls are maximised.
    // BSTA.
    // Greedily try to place every ball k distance apart.
    // if possible, then increase k.
    const auto n = static_cast<int>(position.size());
    std::ranges::sort(position);
    auto feasible = [&](int k) {
      auto placed = 1;
      auto prevPosition = position[0];

      for (int i = 1; i < n; ++i) {
        if (auto distance = position[i] - prevPosition; distance >= k) {
          ++placed;
          prevPosition = position[i];
        }

        if (placed >= m) {
          return true;
        }
      }

      return false;
    };

    int left = 1;
    int right = (position.back() - position.front()) / (m - 1);
    while (left < right) {
      auto mid = left + (right - left + 1) / 2;
      if (feasible(mid)) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    return left;
  }
};
