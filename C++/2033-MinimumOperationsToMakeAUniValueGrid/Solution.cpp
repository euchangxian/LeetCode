#include <algorithm>
#include <cmath>
#include <vector>

class Solution {
 public:
  int minOperations(std::vector<std::vector<int>>& grid, int x) {
    // In each operation: grid[i][j] +- x.
    // Minimum operations to make all elements equal.
    // Average?
    // Median.
    // Given n*m, which must be an even number, there are two possible Medians
    // to consider (except for the case where n=1, and m=1).
    //
    // Is there a way to do it without n*m extra space?
    // Get the median(s) of every row? Then get the median of the medians.
    // O(2*n) extra space? Nope. This only finds the approximate median.
    const int n = grid.size();
    const int m = grid[0].size();

    // Guaranteed to have two medians, except for the case where n=1, m=1...
    // Then, the answer is trivially 0.
    if (n == 1 && m == 1) {
      return 0;
    }

    auto countOps = [&grid, x](int target) -> int {
      int ops = 0;
      for (const auto& row : grid) {
        for (int num : row) {
          int diff = std::abs(target - num);
          if (diff % x != 0) {
            return -1;
          }
          ops += diff / x;
        }
      }
      return ops;
    };

    std::vector<int> flattened;
    flattened.reserve(n * m);
    for (const auto& row : grid) {
      flattened.insert(flattened.end(), row.begin(), row.end());
    }

    int mid = flattened.size() / 2;

    std::nth_element(flattened.begin(), flattened.begin() + mid,
                     flattened.end());
    int minOps1 = countOps(flattened[mid]);

    std::nth_element(flattened.begin(), flattened.begin() + mid - 1,
                     flattened.begin() + mid);
    int minOps2 = countOps(flattened[mid - 1]);

    if (minOps1 == -1) {
      return minOps2;
    }
    if (minOps2 == -1) {
      return minOps1;
    }
    return std::min(minOps1, minOps2);
  }
};
