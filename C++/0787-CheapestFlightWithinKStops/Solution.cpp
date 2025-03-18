#include <algorithm>
#include <vector>

constexpr int INF = 10e4 + 1;

class Solution {
 public:
  int findCheapestPrice(int n,
                        std::vector<std::vector<int>>& flights,
                        int src,
                        int dst,
                        int k) {
    // Bellman Ford. The invariant of Bellman Ford is such that after the ith
    // iteration, nodes that are i hops away have the correct distance estimates
    std::vector<int> prices(n, INF);
    prices[src] = 0;

    // Only k iterations needed
    for (int i = 0; i < k + 1; ++i) {
      // A temporary array is required to ensure that the constraint of k stops
      // is not violated
      std::vector<int> temp = prices;
      for (const auto& edge : flights) {
        int from = edge[0];
        int to = edge[1];
        int price = edge[2];

        temp[to] = std::min(temp[to], prices[from] + price);
      }

      prices = std::move(temp);
    }

    if (prices[dst] == INF) {
      return -1;
    }

    return prices[dst];
  }
};
