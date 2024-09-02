#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
private:
  int const INF = 10e4 + 1;

public:
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst,
                        int k) {
    // Bellman Ford. The invariant of Bellman Ford is such that after the ith
    // iteration, nodes that are i hops away have the correct distance estimates
    vector<int> prices(n, INF);
    prices[src] = 0;

    // Only k iterations needed
    for (int i = 0; i < k + 1; ++i) {
      // A temporary array is required to ensure that the constraint of k stops
      // is not violated
      vector<int> temp = prices;
      for (auto const &edge : flights) {
        int from = edge[0];
        int to = edge[1];
        int price = edge[2];

        temp[to] = min(temp[to], prices[from] + price);
      }

      prices = std::move(temp);
    }

    if (prices[dst] == INF) {
      return -1;
    }

    return prices[dst];
  }
};
