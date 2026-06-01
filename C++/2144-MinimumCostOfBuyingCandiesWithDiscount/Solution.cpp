#include <algorithm>
#include <functional>
#include <vector>

class Solution {
 public:
  int minimumCost(std::vector<int>& cost) {
    // For every two candies sold, shop gives a third for free.
    // Choose any third candy that has cost <= first two candy.
    // Return the minimum cost of buying all the candies.
    //
    // Greedy.
    const auto n = static_cast<int>(cost.size());
    std::ranges::sort(cost, std::greater<>{});
    auto result = 0;
    for (int i = 0; i < n; ++i) {
      if ((i + 1) % 3 == 0) {
        continue;
      }
      result += cost[i];
    }
    return result;
  }
};
