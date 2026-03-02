#include <algorithm>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  int minSwaps(std::vector<std::vector<int>>& grid) {
    // nxn binary grid.
    // In one step: choose two adjacent rows and swap them.
    // A grid is said to be valid if all the cells above the main diagonals are
    // zeros.
    // Return the minimum number of swaps required to make the grid valid, or
    // -1 if not.
    //
    // n <= 200
    // Feels like sorting.
    // We do not need to keep track of all the zeros. Merely the position of the
    // right-most '1' in each row.
    //
    // How do we obtain the minimum swaps though?
    // Distance from a row's sorted position?
    // In one-swap?
    const auto n = static_cast<int>(grid.size());
    std::vector<int> positions;
    positions.reserve(n);

    for (const auto& row : grid) {
      positions.push_back(-1);
      for (int i = n - 1; i >= 0; --i) {
        if (row[i] == 1) {
          positions.back() = i;
          break;
        }
      }
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
      auto sortedIdx = -1;
      for (int j = i; j < n; ++j) {
        if (positions[j] <= i) {
          result += j - i;
          sortedIdx = j;
          break;
        }
      }

      if (sortedIdx == -1) {
        return -1;
      }

      for (int j = sortedIdx; j > i; --j) {
        std::swap(positions[j], positions[j - 1]);
      }
    }

    return result;
  }
};
