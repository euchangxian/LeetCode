#include <algorithm>
#include <climits>
#include <cstddef>
#include <vector>

class Solution {
 public:
  int minCost(std::vector<std::vector<int>>& costs) {
    // Already did Paint House II that has k colours instead of 3...
    const std::size_t n = costs.size();
    const std::size_t k = costs[0].size();  // k is technically just 3.

    for (std::size_t i = 1; i < n; ++i) {
      for (std::size_t j = 0; j < k; ++j) {
        int minCost = INT_MAX;
        for (std::size_t c = 0; c < k; ++c) {
          if (c == j) {
            continue;
          }
          minCost = std::min(minCost, costs[i - 1][c]);
        }
        costs[i][j] += minCost;
      }
    }

    return *std::min_element(costs[n - 1].begin(), costs[n - 1].end());
  }
};
